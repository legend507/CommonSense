import certifi
import urllib3
import sys
import requests

http = urllib3.PoolManager(
    cert_reqs='CERT_REQUIRED',
    ca_certs=certifi.where()    )
my_user_agent = 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/67.0.3396.99 Safari/537.36'
refer = 'https://finance.yahoo.com/quote/%5EN225/history?period1=-157453200&period2=1530802800&interval=1d&filter=history&frequency=1d'

r = http.request('GET', 
                 refer)

print(r.headers['set-cookie'])


# headers = {
#     'referer' : refer,
#     'user-agent' : my_user_agent,
#     'cookie' : 100
#     }

# download_url = 'https://query1.finance.yahoo.com/v7/finance/download/^N225?period1=-157453200&amp;period2=1530802800&amp;interval=1d&amp;events=history&amp;crumb=I.8YZ7XmJ.z'

# r = http.request('GET', 
#                  download_url, headers = headers )

# print(r.status)

# oFile = open('./test.csv', 'wb')
# oFile.write(r.data)
# oFile.close()
# print("Stock: Test Updated")

