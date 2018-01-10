    def readOneFolder(self, folderPath):
        for root, subdirs, files in os.walk(folderPath):
            print('----------------')
            print(root)
            print(subdirs)
            print(files)