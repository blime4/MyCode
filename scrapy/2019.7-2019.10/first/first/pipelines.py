# -*- coding: utf-8 -*-

# Define your item pipelines here
#
# Don't forget to add your pipeline to the ITEM_PIPELINES setting
# See: https://docs.scrapy.org/en/latest/topics/item-pipeline.html
# import json


# 版本一
# class FirstPipeline(object):
#     def __init__(self):
#         self.fp = open("duanzi.json","w",encoding="utf-8")

#     def open_item(self, spider):
#         print('爬虫开始-----')

#     def process_item(self, item, spider):
#         item_json = json.dumps(dict(item),ensure_ascii=False)
#         self.fp.write(item_json+'\n')
#         return item

#     def close_item(self, spider):
#         self.fp.close()
#         print('爬虫结束')

#版本二
# from scrapy.exporters import JsonItemExporter

# class FirstPipeline(object):
#     def __init__(self):
#         self.fp = open("duanzi.json","wb")
#         self.exporters = JsonItemExporter(self.fp, ensure_ascii=False,encoding='utf-8')
#         self.exporters.start_exporting()

#     def open_item(self, spider):
#         print('爬虫开始-----')

#     def process_item(self, item, spider):
#         self.exporters.export_item(item)
#         return item

#     def close_item(self, spider):
#         self.exporters.finish_exporting()
#         self.fp.close()
#         print('爬虫结束')

#版本三 简单高效方便
from scrapy.exporters import JsonLinesItemExporter

class FirstPipeline(object):
    def __init__(self):
        self.fp = open("duanzi.json","wb")
        self.exporters = JsonLinesItemExporter(self.fp, ensure_ascii=False)
    def open_item(self, spider):
        pass

    def process_item(self, item, spider):
        self.exporters.export_item(item)
        return item

    def close_item(self, spider):
        self.fp.close()
        