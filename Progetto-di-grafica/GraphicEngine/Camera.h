#pragma once
/*This class represents a camera. Settings should comprise both orthographic and
 * perspective projections, and the necessary math to retrieve the camera
 * inverse matrix.*/

class Camera : public Node {
 public:
  Camera();
  virtual ~Camera();
  void setProjectionMatrix(glm::mat4 projection);
  void render(glm::mat4 renderMatrix);
  void setMovable(bool movable);
  bool getMovable();
  
  void setVec(glm::vec3 eye, glm::vec3 center, glm::vec3 up);
  glm::vec3 getEye();
  glm::vec3 getCenter();
  glm::vec3 getUp();

 private:
  glm::mat4 projectionMatrix;
  glm::vec3 eye;
  glm::vec3 center;
  glm::vec3 up;
  bool movable = false;
};