#ifndef RAYLIB_CPP_PHYSICS_HPP_
#define RAYLIB_CPP_PHYSICS_HPP_

#ifdef __cplusplus
extern "C"
{
#endif
#include "physac.h"
#include "raylib.h"
#ifdef __cplusplus
}
#endif

#include "./Vector2.hpp"

namespace raylib
{
class Physics
{
public:
  Physics()
  {
    Init();
  };
  Physics(float gravityX, float gravityY)
  {
    Init();
    SetGravity(gravityX, gravityY);
  };

  ~Physics()
  {
    Close();
  }

  inline Physics &Init()
  {
    ::InitPhysics();
    return *this;
  }

  inline Physics &Close()
  {
    ::ClosePhysics();
    return *this;
  }

  inline Physics &RunStep()
  {
    ::RunPhysicsStep();
    return *this;
  }

  inline Physics &SetTimeStep(double delta)
  {
    ::SetPhysicsTimeStep(delta);
    return *this;
  }

  inline bool IsEnabled()
  {
    return ::IsPhysicsEnabled();
  }

  inline Physics &SetGravity(float x, float y)
  {
    ::SetPhysicsGravity(x, y);
    return *this;
  }

  inline PhysicsBody CreateBodyCircle(Vector2 pos, float radius, float density)
  {
    return ::CreatePhysicsBodyCircle(pos, radius, density);
  }
  inline PhysicsBody CreateBodyRectangle(Vector2 pos, float width, float height, float density)
  {
    return ::CreatePhysicsBodyRectangle(pos, width, height, density);
  }
  inline PhysicsBody CreateBodyPolygon(Vector2 pos, float radius, int sides, float density)
  {
    return ::CreatePhysicsBodyPolygon(pos, radius, sides, density);
  }
  inline Physics &AddForce(PhysicsBody body, Vector2 force)
  {
    ::PhysicsAddForce(body, force);
    return *this;
  }
  inline Physics &AddTorque(PhysicsBody body, float amount)
  {
    ::PhysicsAddTorque(body, amount);
    return *this;
  }
  inline Physics &Shatter(PhysicsBody body, Vector2 position, float force)
  {
    ::PhysicsShatter(body, position, force);
    return *this;
  }
  inline int GetBodiesCount()
  {
    return ::GetPhysicsBodiesCount();
  }
  inline PhysicsBody GetBody(int index)
  {
    return ::GetPhysicsBody(index);
  }
  inline int GetShapeType(int index)
  {
    return ::GetPhysicsShapeType(index);
  }
  inline int GetShapeVerticesCount(int index)
  {
    return ::GetPhysicsShapeVerticesCount(index);
  }
  inline Vector2 GetShapeVertex(PhysicsBody body, int vertex)
  {
    return ::GetPhysicsShapeVertex(body, vertex);
  }
  inline Physics &SetBodyRotation(PhysicsBody body, float radians)
  {
    ::SetPhysicsBodyRotation(body, radians);
    return *this;
  }
  inline Physics &DestroyBody(PhysicsBody body)
  {
    ::DestroyPhysicsBody(body);
    return *this;
  }
  inline Physics &Reset()
  {
    ::ResetPhysics();
    return *this;
  }
};
} // namespace raylib

#endif
