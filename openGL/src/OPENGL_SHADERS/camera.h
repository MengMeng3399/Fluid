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


//ö������  ����������ƶ���������;
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

    //��������ʼ�������,���г�ʼֵ �������п���ʲô����д��Ҳ�����������¸�ֵ��
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
        float yaw = YAW, float pitch = PITCH);

     //��ʸ����ʼ�������
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

    //�������� --> �۲����꣨view��
    glm::mat4 GetViewMatrix();

    //���̶˵Ĳ��������������ƶ�
    //������κ����Ƽ��̵�����ϵͳ���յ����롣�������������ö����ʽ������������Ӵ���ϵͳ����ȡ�� 
    void ProcessKeyboard(Camera_Movement direction, float deltaTime);

    //���˵Ĳ���
    //������������ϵͳ���յ����롣��Ҫx��y�����ƫ��ֵ
    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);

    //�������Ĳ���,����Ҫ�ڴ�ֱ������������ 
    void ProcessMouseScroll(float yoffset);

private:

    //ŷ���Ǹ���
    void updateCameraVectors();
};