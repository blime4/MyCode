# -*- coding: utf-8 -*-
import scrapy
from news.items import NewsItem

class XinwenriridiSpider(scrapy.Spider):
    name = 'xinwenriridi'
    allowed_domains = ['http://mp.weixin.qq.com']
    start_urls = ['http://mp.weixin.qq.com/profile?src=3&timestamp=1563983177&ver=1&signature=jQLF2-Km9C-qKBjmp*SObGjMKD5lc*EEl9gUmxIqw0s3ka4JvTS35d9pzs92JrjcYdZcqiYmBBAq-C10Z7AuLg==']

    def parse(self, response):
        wenzhangs = response.xpath("//div[@class=weui_msg_card]//div[@class=weui_media_bd]") 
        for wenzhang in wenzhangs:
            title = wenzhang.xpath("./h4/text()").get()
            print('-'*40)
            print(title)
            print('-'*40)
