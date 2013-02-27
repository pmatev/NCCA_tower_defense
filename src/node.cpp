#include "fwd/entity.h"
#include "entity.h"
#include "node.h"
#include "renderer.h"
#include "game.h"

#define PI 3.14159265

//-------------------------------------------------------------------//

Node::Node(const ngl::Vec3 &_pos, float _hexagonSize, unsigned int _id):
  Entity(_pos, NODE,_id),
  m_isOccupied(false),
  m_hexagonSize(_hexagonSize),
  m_highlighted(false),
  m_isVisible(true),
  m_isFound(false),
  m_searchDepth(-1)
{
  //variables initialised before constructor body called
  m_transformStack.setPosition(m_pos);
  generateMesh();
  publish();
}

//-------------------------------------------------------------------//

NodePtr Node::create(const ngl::Vec3 &_pos, float _hexagonSize)
{
  //get a pointer to the game
  Game* game = Game::instance();
  unsigned int id = game->getID();
  NodePtr a(
        new Node(
          _pos,
          _hexagonSize,
          id
          )
        );
  game->registerID(a, id);
  return a;
}

//-------------------------------------------------------------------//

Node::~Node()
{
  //currently using default destructor
  std::cout<<"deleting node "<<m_ID<<std::endl;
}

void Node::generateMesh()
{
  const static GLubyte indices[]=  {
                                      0,1,5, // back
                                      1,2,3, // front
                                      3,4,5, // top
                                      1,3,5
                                   };

  GLfloat vertices[] = {-m_hexagonSize/2, 0.0, 0.0,
                        -m_hexagonSize/4, 0.0, std::cos(30*PI/180)*m_hexagonSize/2,
                        m_hexagonSize/4, 0.0, std::cos(30*PI/180)*m_hexagonSize/2,
                        m_hexagonSize/2, 0.0, 0.0,
                        m_hexagonSize/4, 0.0, -(std::cos(30*PI/180)*m_hexagonSize/2),
                        -m_hexagonSize/4, 0.0, -(std::cos(30*PI/180)*m_hexagonSize/2),
                       };
  GLfloat normals[] = {0.1,0.1,0.1,
                       0.1,0.1,0.1,
                       0.1,0.1,0.1,
                       0.1,0.1,0.1,
                       0.1,0.1,0.1,
                       0.1,0.1,0.1
                       };

  std::vector<Renderer::vertData> boxData;
  Renderer::vertData d;
  for(int j=0; j<12; j++)
  {
    d.x = vertices[j*3];
    d.y = vertices[(j*3)+1];
    d.z = vertices[(j*3)+2];
    d.nx = normals[j*3];
    d.ny = normals[(j*3)+1];
    d.nz = normals[(j*3)+2];

    boxData.push_back(d);
  }

  unsigned int vertSize = sizeof(Renderer::vertData);
  Renderer *render = Renderer::instance();

  render->createVAO(m_IDStr, GL_TRIANGLES);

  render->setIndexedDataToVAO(m_IDStr,
                              vertSize*boxData.size(),
                              3,
                              boxData[0].x,
                              sizeof(indices),
                              &indices[0],
                              12);

}



//-------------------------------------------------------------------//


void Node::update(const double _dt)
{
  //Q unused to remove warnings, will be replaced if used

  Q_UNUSED(_dt);
}

//-------------------------------------------------------------------//

//void Node::draw()
//{
//  Renderer *r = Renderer::instance();
//  r->loadMatrixToShader(m_transformStack, "Phong");
//  if(m_highlighted == false)
//  {
//      r->draw(m_IDStr, "Phong");
//      //std::cout<<"POS: "<<m_transformStack<<std::endl;
//  }
//  else
//  {
//      std::cout<<"rendering selected node "<<m_ID<<std::endl;
//      r->draw(m_IDStr, "Phong"); //change either shader or colour

//      //need to change this system for changing highlighted back
//      // at uiselection level

//  }



//}

////-------------------------------------------------------------------//

//void Node::drawSelection()
//{
//  Renderer *r = Renderer::instance();
//  r->loadMatrixToShader(m_transformStack, "Colour");
//  r->drawSelection(m_ID, m_IDStr);
//}

////-------------------------------------------------------------------//

//-------------------------------------------------------------------//

void Node::resetSearchInfo()
{
  m_isFound = false;
  // This is set to -1 so that if it is not found when we search tree we know
  // that there is no valid path from here to the goal
  m_searchDepth = -1;
}

//-------------------------------------------------------------------//

void Node::filterViewVolume(EntityRecordList &o_localEntities)
{
  Q_UNUSED(o_localEntities);
}

//-------------------------------------------------------------------//

void Node::generateViewBBox()
{
  // initialise world space view box
  m_wsViewBBox = BBox(
        m_lsMeshBBox.m_minX*5 + m_pos.m_x,
        m_lsMeshBBox.m_minY*5 + m_pos.m_y,
        m_lsMeshBBox.m_minZ*5 + m_pos.m_z,
        m_lsMeshBBox.m_maxX*5 + m_pos.m_x,
        m_lsMeshBBox.m_maxY*5 + m_pos.m_y,
        m_lsMeshBBox.m_maxZ*5 + m_pos.m_z
        );
}

//-------------------------------------------------------------------//

void Node::draw()
{
  if(m_isVisible)
  {
    if(m_isInSpawnPath)
    {
      drawWithColour(ngl::Vec3(0, 0, 1));
    }
    else
    {
      drawWithColour(ngl::Vec3(1, 0, 0));
    }
  }
}

//-------------------------------------------------------------------//

void Node::setVisibility(bool _visibility)
{
  m_isVisible = _visibility;
}
