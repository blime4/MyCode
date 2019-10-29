# JupyterNotebook插件管理与安装

## 依赖安装

JupyterNotebook本身有推荐的插件管理包。 
 我们首先需要安装如下第三方库用于管理JupyterNotebook插件。

```
pip install jupyter_nbextensions_configuratorpip install jupyter_contrib_nbextensions
```

安装完成后，我们还需要执行如下命令来完成插件管理启用：

```
jupyter nbextensions_configurator enable --userjupyter contrib nbextension install --user
```

[参考链接](https://www.missshi.cn/api/view/blog/5ab10ef65b925d0d4e000001)

