# 程设分组训练 任务5

## 设计文档

### 程序参数设计

1. 子任务1

| argc[x] | 参数名称 | 参数类型 | 参数说明 | 合法性检查 |
| ---- | ------- | ------- | --------- | --------- |
| 1 | path | char* | 英文文档txt路径 | 可访问 |
| 2 | is_detailed | int | 是否为细节模式 | 0/1，其余报错 |

2. 子任务2

| argc[x] | 参数名称 | 参数类型 | 参数说明 | 合法性检查 |
| ---- | ------- | ------- | --------- | --------- |
| 1 | path | char* | 统计结果文件路径 | 可访问 |
| 2 | is_detailed | int | 是否为细节模式 | 0/1，其余报错 |

### 工作目录设计

```plaintext

(root)
|- raw_processor.cpp
|- analysis_processor.cpp
|- run.cpp
|- result.html (最终结果文件，如果只有一个内容则自动跳转)
|- (texts)
   |- 原文放置在这里，例如：sometext.txt
|- (data)
    |- (analysed_data)
        |- 统计信息放在这里，例如：exp[序号]/sometext.txt
    |- (html_storage)
        |- 多任务生成的html文件放在这里，文件名格式如：exp[序号]/sometext.html

```