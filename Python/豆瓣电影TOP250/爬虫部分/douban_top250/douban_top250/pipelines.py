# Define your item pipelines here
#
# Don't forget to add your pipeline to the ITEM_PIPELINES setting
# See: https://docs.scrapy.org/en/latest/topics/item-pipeline.html


# useful for handling different item types with a single interface
from itemadapter import ItemAdapter
import sqlite3


class DoubanTop250Pipeline:
    def __init__(self):
        self.conn = sqlite3.connect("douban.db")
        self.c = self.conn.cursor()
        self.c.execute(
            """CREATE TABLE IF NOT EXISTS DOUBAN_TOP250 (
            id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
            title TEXT NOT NULL,
            rank REAL NOT NULL,
            theme TEXT NOT NULL,
            nationality TEXT NOT NULL);"""
        )

    def close_spider(self, spidef):
        self.conn.commit()
        self.conn.close()

    def process_item(self, item, spider):
        title = item.get("title", " ")
        rank = item.get("rank", " ")
        theme = item.get("theme", " ")
        nationality = item.get("nationality", " ")
        self.c.execute(
            f'INSERT INTO DOUBAN_TOP250 (title, rank, theme,nationality) VALUES ("{title}",{rank},"{theme}","{nationality}")'
        )
        return item
