import requests
import lxml
import json
import time

headers = {
    'user-agent':'Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:72.0) Gecko/20100101 Firefox/72.0'
}

def get_news():
    url='https://opendata.baidu.com/data/inner?tn=reserved_all_res_tn&dspName=iphone&from_sf=1&dsp=iphone&resource_id=28565&alr=1&query=%E8%82%BA%E7%82%8E&cb=jsonp_1581048165763_37055'
    html = requests.get(url,headers=headers)
    start = html.text.find('{"ResultCode"')
    end = html.text.find(r'mock_recall_srcids\u0000\u0000"}')+len(r'mock_recall_srcids\u0000\u0000"}')
    json_data = json.loads(html.text[start:end])
    json_data = json_data['Result'][0]['DisplayData']['result']['items']
    for data in json_data:
        print(data['eventDescription'])
        current_time = time.localtime(int(data['eventTime']))
        print(time.strftime("%Y-%m-%d %H:%M:%S",current_time))
        print(data['eventUrl'])

if __name__ == '__main__':
    get_news()