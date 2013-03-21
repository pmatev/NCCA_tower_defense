#include "ngl/ShaderLib.h"

#include "fwd/entity.h"
#include "entity.h"
#include "node.h"
#include "renderer.h"
#include "game.h"
#include "window.h"

#define PI 3.14159265

//-------------------------------------------------------------------//

Node::Node(const ngl::Vec3 &_pos, float _hexagonSize, unsigned int _id):
  Entity(_pos, NODE,_id),
  m_isOccupied(false),
  m_hexagonSize(_hexagonSize),
  m_highlighted(0),
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

}

void Node::generateMesh()
{
  const static GLubyte indices[]=  {
                                      0,1,5,
                                      1,2,3,
                                      3,4,5,
                                      1,3,5
                                   };

  GLfloat vertices[] = {-m_hexagonSize/2, 0.0, 0.0,
                        -m_hexagonSize/4, 0.0, std::cos(30*PI/180)*m_hexagonSize/2,
                        m_hexagonSize/4, 0.0, std::cos(30*PI/180)*m_hexagonSize/2,
                        m_hexagonSize/2, 0.0, 0.0,
                        m_hexagonSize/4, 0.0, -(std::cos(30*PI/180)*m_hexagonSize/2),
                        -m_hexagonSize/4, 0.0, -(std::cos(30*PI/180)*m_hexagonSize/2),
                       };
  GLfloat normals[] = {0.8,0.8,0.8,
                       0.8,0.8,0.8,
                       0.8,0.8,0.8,
                       0.8,0.8,0.8,
                       0.8,0.8,0.8,
                       0.8,0.8,0.8
                       };

  // CALCULATE UVs FROM VERTs (PLANAR MAP)

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

void Node::resetSearchInfo()
{
  m_isFound = false;
  // This is set to -1 so that if it is not found when we search tree we know
  // that there is no valid path from here to the goal
  m_searchDepth = -1;
}

//-------------------------------------------------------------------//

void Node::filterViewVolume(EntityRecordWCList &o_localEntities)
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
        Renderer *r = Renderer::instance();

        ngl::ShaderLib *shader = ngl::ShaderLib::instance();

        (*shader)["Phong"]->use();
        r->loadMatrixToShader(m_transformStack.getCurrentTransform().getMatrix(), "Phong");
        ngl::Vec3 c = Window::instance()->IDToColour(m_ID);
        c = c/255.0f;

        shader->setShaderParam4f("colourSelect", c[0], c[1], c[2], 1);

        if(m_highlighted == 1)
        {
            shader->setShaderParam4f("colour", 0, 0, 0, 1);
        }
        else if(m_highlighted == 2)
        {
            shader->setShaderParam4f("colour", 1, 0, 1, 1);
        }
        else if(m_isInSpawnPath)
        {
            shader->setShaderParam4f("colour", 0, 0, 1, 1);
        }
        else
        {
            shader->setShaderParam4f("colour", 0.8, 0.8, 0.8, 1);
        }

        r->draw("hexagon", "Phong");

    }


}

//-------------------------------------------------------------------//

void Node::setVisibility(bool _visibility)
{
  m_isVisible = _visibility;
}
