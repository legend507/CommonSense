
import requests

fileName = 'test.txt'

files = {'file': open(fileName, 'rb')}
print('sending:', fileName)
r = requests.post('http://10.229.81.17:8080', files=files)
print(r.request.headers)