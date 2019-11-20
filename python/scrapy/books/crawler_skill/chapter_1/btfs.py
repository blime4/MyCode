from urllib.request import urlopen
from bs4 import BeautifulSoup
r = urlopen('http://www.baidu.com')
bs = BeautifulSoup(r.read(), 'html.parser')
print(bs.title)