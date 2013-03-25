#ifndef STANDARDWALL_H
#define STANDARDWALL_H

#include "staticentity.h"

class StandardWall : public StaticEntity
{
public:
  static EntityPtr create(NodePtr _linkedNode, unsigned int _id);
  void update(double _dt);
  void filterViewVolume(EntityRecordWCList &o_localEntities);
  void generateViewBBox();
  void draw();
protected:
  StandardWall(NodePtr _linkedNode, unsigned int _id);
};

#endif // STANDARDWALL_H
