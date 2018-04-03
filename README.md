## 停车场模拟管理程序的设计与实现

#### 问题描述

设停车场只有一个可停放几辆汽车的狭长通道，且只有一个大门可供汽车进出。汽车在停车场内按车辆到达的先后顺序依次排列，若车场内已停满几辆汽车，则后来的汽车只能在门外的便道上等候，一旦停车场内有车开走，则排在便道上的第一辆车即可进入；当停车场内某辆车要离开时，由于停车场是狭长的通道，在它之后开入的车辆必须先退出车场为它让路，待该车辆开出大门，为它让路的车辆再按原次序进入车场。在这里假设汽车不能从便道上开走，试设计这样一个停车厂模拟管理程序。

#### 展示

>按下按钮小车进栈

![](http://7xkl1b.com1.z0.glb.clouddn.com/cocosCar_1.png)
>车库满了在外面队列等待

![](http://7xkl1b.com1.z0.glb.clouddn.com/cocosCar_2.png)
>按其中一辆小车，后面的车退到等待栈，该车出车库开走，然后进入

![](http://7xkl1b.com1.z0.glb.clouddn.com/cocosCar_3.png)
