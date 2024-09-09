@echo off
SetLocal EnableDelayedExpansion
(set PATH=C:\Users\idole\MyFiles\Qt_5_15\5.15.2\mingw81_32\bin;!PATH!)
if defined QT_PLUGIN_PATH (
    set QT_PLUGIN_PATH=C:\Users\idole\MyFiles\Qt_5_15\5.15.2\mingw81_32\plugins;!QT_PLUGIN_PATH!
) else (
    set QT_PLUGIN_PATH=C:\Users\idole\MyFiles\Qt_5_15\5.15.2\mingw81_32\plugins
)
%*
EndLocal
