# Unicode2GBK

```python
import json
import codecs
import os


class JsonWithEncodingPipeline(object):

    def __init__(self):
        self.file = codecs.open('scraped_data_GBK.json', 'w', encoding='GBK')
        self.file.write('[')

    def process_item(self, item, spider):
        line = json.dumps(dict(item), ensure_ascii=False) + "\n"
        self.file.write(line+',')
        return item

    def close_spider(self, spider):
        self.file.seek(-1, os.SEEK_END)
        self.file.truncate();
        self.file.write(']')
        self.file.close()  
```

```python
#settings.py
ITEM_PIPELINES = {
    'JsonWithEncodingPipeline':300,
}
```

