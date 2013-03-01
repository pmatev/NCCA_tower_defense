#ifndef INVISIBLEWALL_H
#define INVISIBLEWALL_H

#include "wall.h"
#include "smartpointers.h"

DECLARESMART(InvisibleWall)

class InvisibleWall : public Wall
{
public:
  static EntityPtr create(NodePtr _linkedNode, unsigned int _id);
  void update(double _dt);
  void draw();
  void filterViewVolume(EntityRecordWCList &o_localEntities);
  void generateViewBBox();
protected:
  InvisibleWall(NodePtr _linkedNode, unsigned int _id);
};

#endif // INVISIBLEWALL_H
