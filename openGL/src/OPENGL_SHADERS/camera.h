#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

// Default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 0.5f;
const float SENSITIVITY = 0.05f;
const float ZOOM = 45.0f;


//枚举类型  定义摄像机移动上下左右;
enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

class Camera
{
public:
    // camera Attributes
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;

    // euler Angles
    float Yaw;
    float Pitch;

    // camera options
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;

    Camera();

    //用向量初始化摄像机,均有初始值 ，括号中可以什么都不写，也可以依次重新赋值。
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
        float yaw = YAW, float pitch = PITCH);

     //用矢量初始化摄像机
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

    //世界坐标 --> 观察坐标（view）
    glm::mat4 GetViewMatrix();

    //键盘端的操作，上下左右移动
    //处理从任何类似键盘的输入系统接收的输入。接受摄像机定义枚举形式的输入参数（从窗口系统中提取） 
    void ProcessKeyboard(Camera_Movement direction, float deltaTime);

    //鼠标端的操作
    //处理从鼠标输入系统接收的输入。需要x和y方向的偏移值
    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);

    //鼠标滚动的操作,仅需要在垂直车轮轴上输入 
    void ProcessMouseScroll(float yoffset);

private:

    //欧拉角更新
    void updateCameraVectors();
};