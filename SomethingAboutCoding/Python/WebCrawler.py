"""
Simple Python 3 web crawler, to be extended for various uses.
Basic Functions:
    Start from one URL, get HTML.
    Traverse the HTML, count work occurance.
    Extract all links in the HTML, append the links to to visit queue.
    Repeat until queue is empty.

Prerequisites:
    pip install requests
    pip install beautifulsoup4
"""
import collections
import string
from timeit import default_timer
from urllib.parse import urldefrag, urljoin, urlparse
import bs4
import requests
import os


class MyWebCrawler:
    def __init__(self, url, maxpages=100, singledomain=True, keywords=False, proxy=None):
        self.startURL = url
        self.maxpages = maxpages                        # limit, how many pages to crawl
        self.singledomain = singledomain                # if only crawl the url in the same domain with the startURL
        self.checkKeyWorkds = keywords                  # if check and summarize keywords in the html page
        self.proxy = proxy

    def crawl(self):
        '''
        main func, 
        '''
        pagequeue = collections.deque()
        pagequeue.append(self.startURL)                                             # to visit url queue, FIFO
        crawled = []                                                                # visited url list
        domain = urlparse(self.startURL).netloc if self.singledomain else None           # domain name of startURL

        crawled_success     = 0     # num of pages successfully crawled
        crawled_fail        = 0     # num of pages failed to crawled

        sess = requests.session()
        while crawled_success < self.maxpages and pagequeue:
            url = pagequeue.popleft()
            print('Requesting: {}'.format(url))

            # send request GET
            try:
                response = sess.get(url, proxies=self.proxy)
            except (requests.exceptions.ConnectionError):
                # try with proxy
                print('**Failed, may need config proxy')
                continue
            except (requests.exceptions.MissingScheme, requests.exceptions.InvalidSchema):
                print('**Failed: {}'.format(url))
                crawled_fail +=1
                continue
            except:
                print('**Something wrong')
                continue
            # got the reply, exam header
            ## if have content-type header
            try:
                response.headers['content-type']
            except:
                print('**No Header: content-type, ignore')
                continue
            ## only process html data, ignore other content
            if not response.headers['content-type'].startswith('text/html'):   continue

            # Beautiful Soup the html
            soup = bs4.BeautifulSoup(response.text, 'html.parser')

            crawled.append(url)
            crawled_success += 1

            # traverse the html page, summarize all keywords
            if self.checkKeyWorkds: self.pageHandler(url, response, soup)

            # get all link from html
            links = self.getLinks(url, domain, soup)
            for link in links:
                print('     Found link: {}'.format(link))
                if not self.url_in_list(link, crawled) and not self.url_in_list(link, pagequeue):
                    pagequeue.append(link)

        print('{0} page crawled, {1} links failed'.format(crawled_success, crawled_fail))

    def pageHandler(self, url, response, soup):
        '''
        Call Sequence: crawl() -> pageHandler()

        This function exam the html text, count occurance of each workds, and find the top 10 words with highest occurance.
        '''
        print(' page length: {}'.format(len(response.text)))
        self.wordCount(soup)

    def wordCount(self, soup):
        '''
        Call Sequence: crawl() -> pageHandler() -> wordCount()
        '''
        rawtext = soup.get_text()
        words = self.getWords(rawtext)
        counts, _ = self.getCounts(words)
        if counts.most_common(1)[0][1] < 10:
            print(' This page does not have any words used more than 10 times.')
        else:
            # print the 10 words that appear the most often
            print(' {}'.format(counts.most_common(10)))

    def getWords(self, rawtext):
        '''
        Call Sequence: crawl() -> pageHandler() -> wordCount() -> getWords()
        '''
        words = []
        cruft = ',./():;!"' + "<>'â{}"          # charset to strip off end of words

        for raw_word in rawtext.split():
            # remove whitespaces before and after a word
            word = raw_word.strip(string.whitespace + cruft + '-').lower()

            # remove posessive 's at the end of word
            if word[-2:] == "'s":
                word = word[:-2]
            # after strip, if word is not empty
            if word:    words.append(word)
        return words

    def getCounts(self, words = None):
        '''
        Call Sequence: crawl() -> pageHandler() -> wordCount() -> getCounts()
        '''
        # a dict with {key=word, value=count}
        counts = collections.Counter(words)
        wordsUsed = len(counts)

        # remove short and common words from dict, word must >= 3 to remain
        shortwords = [word for word in counts if len(word) < 3]
        ignore = shortwords + \
            ['after', 'all', 'and', 'are', 'because', 'been', 'but', 'for', 'from',
                'has', 'have', 'her', 'more', 'not', 'now', 'our', 'than', 'that',
                'the', 'these', 'they', 'their', 'this', 'was', 'were', 'when', 'who',
                'will', 'with', 'year', 'hpv19slimfeature', 'div']
        for word in ignore:
            counts.pop(word, None)

        tempcopy = [_ for _ in words]
        for word in tempcopy:
            if self.noalpha(word):
                counts.pop(word, None)
        return (counts, wordsUsed)

    def noalpha(self, word):
        '''
        Call Sequence: crawl() -> pageHandler() -> wordCount() -> getCounts() -> noalpha()
        '''
        for char in word:
            if char.isalpha():
                return False
        return True
    
    def getLinks(self, url, domain, soup):
        '''
        Call Sequence: crawl() -> getLinks()

        This function exam the html text, extract all links in it.
        '''
        # get target URLs for all links in the html
        links = [a.attrs.get('href') for a in soup.select('a[href]')]

        # remove fragment identifiers
        links = [urldefrag(link)[0] for link in links]

        # remove empty strings
        links = [link for link in links if link]

        # convert relative link to absolute
        links = [link if bool(urlparse(link).netloc) else urljoin(url, link) for link in links]

        # if singledomain == True
        if self.singledomain:
            links = [link for link in links if self.samedomain(urlparse(link).netloc, domain)]

        return links

    def samedomain(self, netloc1, netloc2):
        '''
        Call Sequence: crawl() -> getLinks() -> samedomain()

        This function decides if netloc1 and netloc2 have the same domain
        '''
        domain1 = netloc1.lower()
        if '.' in domain1:
            domain1 = domain1.split('.')[-2] + '.' + domain1.split('.')[-1]

        domain2 = netloc2.lower()
        if '.' in domain2:
            domain2 = domain2.split('.')[-2] + '.' + domain2.split('.')[-1]
        return (domain1 == domain2)

    def url_in_list(self, url, listobj):
        '''
        Call Sequence: crawl() -> url_in_list()
        '''
        http_version = url.replace('https://', 'http://')
        https_version = url.replace('http://', 'https://')
        return (http_version in listobj) or (https_version in listobj)

#------------------------------------------------------------------------------
# if running standalone, crawl yahoo finance url for test
if __name__ == "__main__":
    # use the following proxy inside of Panasonic
    proxy = {
        'http'  :   'http://proxy.mei.co.jp:8080',
        'https' :   'https://proxy.mei.co.jp:8080',
        }
    url = 'https://finance.yahoo.com/quote/%5EN225/history?period1=-157453200&period2=1530802800&interval=1d&filter=history&frequency=1d'
    START = default_timer()
    #---
    wc = MyWebCrawler(url, keywords=False, proxy=proxy)
    wc.crawl()
    #---
    END = default_timer()
    print('Elapsed time (seconds) = ' + str(END-START))