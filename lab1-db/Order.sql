-- 创建数据库
CREATE DATABASE Orders IF NOT EXISTS;

-- 使用数据库
\c Orders;

-- 仓库表
CREATE TABLE "仓库" (
    "仓库号" VARCHAR(50) PRIMARY KEY,
    "城市" VARCHAR(50),
    "面积" INTEGER
);

-- 供应商表
CREATE TABLE "供应商" (
    "供应商号" VARCHAR(50) PRIMARY KEY,
    "供应商名" VARCHAR(50),
    "地址" VARCHAR(50)
);

-- 职工表
CREATE TABLE "职工" (
    "职工号" VARCHAR(50) PRIMARY KEY,
    "仓库号" VARCHAR(50),
    "工资" INTEGER,
    FOREIGN KEY ("仓库号") REFERENCES "仓库"("仓库号")
);

-- 订购单表
CREATE TABLE "订购单" (
    "订购单号" VARCHAR(50) PRIMARY KEY,
    "供应商号" VARCHAR(50),
    "职工号" VARCHAR(50),
    "订购日期" DATE,
    FOREIGN KEY ("供应商号") REFERENCES "供应商"("供应商号"),
    FOREIGN KEY ("职工号") REFERENCES "职工"("职工号")
);

-- 插入 仓库 数据
INSERT INTO "仓库" ("仓库号", "城市", "面积") VALUES
('WH1', '北京', 370),
('WH2', '上海', 500),
('WH3', '广州', 200),
('WH4', '武汉', 400);

-- 插入 供应商 数据
INSERT INTO "供应商" ("供应商号", "供应商名", "地址") VALUES
('S3', '振华电子厂', '西安'),
('S4', '华通电子公司', '北京'),
('S6', '607厂', '郑州'),
('S7', '爱华电子厂', '北京');

-- 插入 职工 数据
INSERT INTO "职工" ("职工号", "仓库号", "工资") VALUES
('E1', 'WH2', 1220),
('E3', 'WH1', 1210),
('E4', 'WH2', 1250),
('E6', 'WH3', 1230),
('E7', 'WH1', 1250);

-- 插入 订购单 数据
INSERT INTO "订购单" ("订购单号", "供应商号", "职工号", "订购日期") VALUES
('OR67', 'S7', 'E3', '2002-06-23'),
('OR73', 'S4', 'E1', '2002-07-28'),
('OR76', 'S4', 'E7', '2002-05-25'),
('OR77', NULL, 'E6', NULL),
('OR79', 'S4', 'E3', '2002-06-13'),
('OR80', NULL, 'E1', NULL),
('OR90', NULL, 'E3', NULL),
('OR91', 'S3', 'E3', '2002-07-13');
