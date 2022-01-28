# 依赖项
依赖项就是一个函数，且可以使用与路径操作函数相同的参数
```python
async def common_parameters(q: Optional[str] = None, skip: int = 0, limit: int = 100):
    return {"q": q, "skip": skip, "limit": limit}

@app.get("/items/")
async def read_items(commons: dict = Depends(common_parameters)):
    return commons
```
依赖项函数的形式和结构与路径操作函数一样。

因此，可以把依赖项当作没有「装饰器」（即，没有 @app.get("/some-path") ）的路径操作函数。

依赖项可以返回各种内容。

本例中的依赖项预期接收如下参数：

类型为 ```str``` 的可选查询参数 q
类型为 int 的可选查询参数 skip，默认值是 0
类型为 int 的可选查询参数 limit，默认值是 100
然后，依赖项函数返回包含这些值的 dict。