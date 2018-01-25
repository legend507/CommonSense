import PyPDF2       # need this lib to deal with PDF files

    # read one PDF file, Panasonic Monthly Income PDF format
    def readPanasonicPDF(self, filePath):
        print(filePath)
        # open PDF file and get all text
        pdf_content = PyPDF2.PdfFileReader(filePath, 'rb')
        page0 = pdf_content.getPage(0).extractText()
        # find all numbers
        #print(page0.encode('shift-JIS', 'ignore'))
        allNumbers = re.findall("\d+", page0)
        print(allNumbers[-4]+','+allNumbers[-3])
        return