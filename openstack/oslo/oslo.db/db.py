#!usr/bin/python
# coding=utf-8

# 使用sqlalchemy链接mariadb创建表格
__author__ = 'fjrti'
from sqlalchemy import create_engine
from sqlalchemy import String, Integer, Column
from sqlalchemy.ext.declarative import declarative_base

engine = create_engine("mysql+pymysql://root:mysql_123456@127.0.0.1/test", encoding="utf-8", echo=True)
Base = declarative_base()


class User(Base):
    __tablename__ = "users"
    id = Column(Integer, primary_key=True)
    name = Column(String(50))
    fullname = Column(String(50))
    password = Column(String(50))

    def __repr__(self):
        return "<User(id=%s,name=%s,fullname=%s,password=%s)>" %\
               (self.id, self.name, self.fullname, self.password)

Base.metadata.create_all(engine)

