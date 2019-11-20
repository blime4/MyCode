# -*- coding: utf-8 -*-

# Define your item pipelines here
#
# Don't forget to add your pipeline to the ITEM_PIPELINES setting
# See: https://docs.scrapy.org/en/latest/topics/item-pipeline.html
import json
import codecs
import os


class JsonWithEncodingPipeline(object):
     
    def __int__(self):
        self.file = codecs.open('article.json', 'w', encoding='utf-8')
        pass
 
    def process_item(self, item, spider):
 
        json_str = json.dumps(dict(item), ensure_ascii=False) + '\n'    # ensure_ascii=False ȷ��д������ʱ��������
        self.file.write(json_str)
 
        return item
 
    def spider_closed(self, spider):    # �� spider �ر�ʱ����ô˺���
        self.file.close()
        
        
class XicidailiPipeline(object):
    def process_item(self, item, spider):
        return item



# -*- coding: utf-8 -*-

# Define your item pipelines here
#
# Don't forget to add your pipeline to the ITEM_PIPELINES setting




