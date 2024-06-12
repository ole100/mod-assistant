# Features


助手是在游戏世界中生成的npc，让玩家获得传家宝、雕文、宝石、诸如派系变化和种族变化之类的实用工具。玩家也可以通过消费金币来提升自己的职业技能。每次使用该特性时，它将被设置为当前的最大值。他们甚至可以解锁飞行路线!

从Assistant获得的所有项目都可以免费购买，但是用户可以通过修改项目模板表的值来轻松添加成本。

通过配置可以启用或禁用上面列出的所有特性——允许用户只使用他们想要的特性。

助理的入口是**9000000**。

个人对代码进行一些更改以及汉化。
Fork来源https://github.com/noisiver/mod-assistant.git，感谢大神

# 使用方法
1，clone 到/azerothcore-wotlk/modules 文件夹。

2，导入位于/azerothcore-wotlk/modules/mod-assistant/data/sql/db-world/base的sql文件到acore_world    

sudo mysql -u acore -p acore_world < mod_assistant.sql    


3,修改位于/azeroth-server/etc/modules  的mod_assistant.conf.dist 配置文件，如果需要。
