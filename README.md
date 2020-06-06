# 学习OpenGL

### 名词解释

| 名词 | 释义 | 详细 |
|-|-|-|
| VAO | 顶点数组对象 | 管理VBO |
| VBO | 顶点缓冲对象 | 在显卡中存储了顶点数据 |
| EBO | 索引缓冲对象 | |

### 显卡管理数据方式

| 枚举 | 含义 |
|-|-|
| `GL_STATIC_DRAW` | 数据不会或几乎不会改变 |
| `GL_DYNAMIC_DRAW` | 数据会被改变很多 |
| `GL_STREAM_DRAW` | 数据每次绘制时都会改变 |

### 图元类型

| 图元类型 | 含义 |
|-|-|
| `GL_POINTS` | 点 |
| `GL_TRIANGLES` | 三角形 |
| `GL_LINE_STRIP` | 直线 |

### 渲染管线

1. 顶点着色器 `*`
2. 图元装配
3. 几何着色器 `*`
4. 光栅化
5. 片段着色器 `*`
6. 测试与混合

注：带 `*` 为可编程，使用 GLSL (OpenGL Shading Language) 语言

### 常用函数

#### 设置绘制模式

```c++
// 线框 GL_LINE
// 填充 GL_FILL
glPolygonMode(GL_FRONT_AND_BACK, GL_LINE)
```