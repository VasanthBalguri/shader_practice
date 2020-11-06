#include "qtosgwidget.h"
#include <iostream>


QtOSGWidget::QtOSGWidget(qreal scaleX, qreal scaleY, QWidget* parent)
      : QOpenGLWidget(parent)
        , _mGraphicsWindow(new osgViewer::GraphicsWindowEmbedded( this->x(), this->y(),
                                                                 this->width(), this->height() ) )
        , _mViewer(new osgViewer::Viewer)
      , m_scaleX(scaleX)
      , m_scaleY(scaleY)
      {

        try{
            //initialize camera
        std::cout<<this->width()<<" "<<this->height();
        camera = new osg::Camera;
        camera->setViewport( this->x(), this->y(), this->width(), this->height() );
        camera->setClearColor( osg::Vec4( 0.9f, 0.9f, 1.f, 1.f ) );
        float aspectRatio = static_cast<float>( this->width()) / static_cast<float>( this->height() );
        camera->setProjectionMatrixAsPerspective( 30.f, aspectRatio, 1.f, 1000.f );
        camera->setGraphicsContext( _mGraphicsWindow );

        _mGraphicsWindow->getState()->setUseModelViewAndProjectionUniforms(true);
        _mGraphicsWindow->getState()->setUseVertexAttributeAliasing(true);

        _mViewer->setCamera(camera);

        //trackball navigation
        osg::ref_ptr<osgGA::TrackballManipulator> manipulator = new osgGA::TrackballManipulator;
        manipulator->setAllowThrow( false );
        this->setMouseTracking(true);
        _mViewer->setCameraManipulator(manipulator);

        osg::ref_ptr<osg::Group> root = new osg::Group;
       // root->addChild(hud_camera);
        _mViewer->setSceneData(root);
        _mViewer->setThreadingModel(osgViewer::Viewer::SingleThreaded);

        _mViewer->realize();
        }
        catch(std::exception e)
        {
            std::cout<<e.what()<<std::endl;
        }

      }

void QtOSGWidget::setScene(osg::ref_ptr<osg::Group> root)
{

    _mViewer->setSceneData(root);
}

osg::ref_ptr<osg::Group> QtOSGWidget::getScene()
{
   osg::ref_ptr<osg::Group> root = dynamic_cast<osg::Group*>(_mViewer->getSceneData());
   return root;
}

void QtOSGWidget::setScale(qreal X, qreal Y)
  {
      m_scaleX = X;
      m_scaleY = Y;
      this->resizeGL(this->width(), this->height());
  }


  void QtOSGWidget::paintGL() {
    _mViewer->frame();
  }

  void QtOSGWidget::resizeGL( int width, int height )
  {
      this->getEventQueue()->windowResize(this->x()*m_scaleX, this->y() * m_scaleY, width*m_scaleX, height*m_scaleY);
      _mGraphicsWindow->resized(this->x()*m_scaleX, this->y() * m_scaleY, width*m_scaleX, height*m_scaleY);
      osg::ref_ptr<osg::Camera> camera = _mViewer->getCamera();
      camera->setViewport(0, 0, this->width()*m_scaleX, this->height()* m_scaleY);
  }

  void QtOSGWidget::initializeGL(){
    //not required for now
  }


  void QtOSGWidget::mouseMoveEvent(QMouseEvent* event)
  {
      this->getEventQueue()->mouseMotion(event->x()*m_scaleX, event->y()*m_scaleY);
  }

  void QtOSGWidget::mousePressEvent(QMouseEvent* event)
  {
      unsigned int button = 0;
      switch (event->button()){
      case Qt::LeftButton:
          button = 1;
          break;
      case Qt::MiddleButton:
          button = 2;
          break;
      case Qt::RightButton:
          button = 3;
          break;
      default:
          break;
      }
      this->getEventQueue()->mouseButtonPress(event->x()*m_scaleX, event->y()*m_scaleY, button);
  }

  void QtOSGWidget::mouseReleaseEvent(QMouseEvent* event)
  {
      unsigned int button = 0;
      switch (event->button()){
      case Qt::LeftButton:
          button = 1;
          break;
      case Qt::MiddleButton:
          button = 2;
          break;
      case Qt::RightButton:
          button = 3;
          break;
      default:
          break;
      }
      this->getEventQueue()->mouseButtonRelease(event->x()*m_scaleX, event->y()*m_scaleY, button);
  }

  void QtOSGWidget::wheelEvent(QWheelEvent* event)
  {
      int delta = event->delta();
      osgGA::GUIEventAdapter::ScrollingMotion motion = delta > 0 ?
                  osgGA::GUIEventAdapter::SCROLL_UP : osgGA::GUIEventAdapter::SCROLL_DOWN;
      this->getEventQueue()->mouseScroll(motion);
  }

  bool QtOSGWidget::event(QEvent* event)
  {
      bool handled = QOpenGLWidget::event(event);
      this->update();
      return handled;
  }

  osgGA::EventQueue* QtOSGWidget::getEventQueue() const {
    osgGA::EventQueue* eventQueue = _mGraphicsWindow->getEventQueue();
    return eventQueue;
  }


  //Where the shaders are added, geometry shader is optional
  void QtOSGWidget::executeShader(std::string vertexShader, std::string fragmentShader, std::string geomShader)
  {
       osg::ref_ptr<osg::StateSet> stateSet = this->getScene()->getOrCreateStateSet();
       osg::ref_ptr<osg::Program> program = new osg::Program;

       osg::ref_ptr<osg::Shader> vertShader = new osg::Shader(osg::Shader::VERTEX, vertexShader);
       if(vertShader.get() == NULL)
       {
           std::cerr<<"unnable to load vertex shader"<<std::endl;
       }
       program->addShader(vertShader);

       if(geomShader.length() != 0)
       {
           osg::ref_ptr<osg::Shader> geometryShader = new osg::Shader(osg::Shader::GEOMETRY, geomShader);
           if(geometryShader.get() == NULL)
           {
               std::cerr<<"unnable to load vertex shader"<<std::endl;
           }
           program->addShader(geometryShader);
        }
       osg::ref_ptr<osg::Shader> fragShader = new osg::Shader(osg::Shader::FRAGMENT, fragmentShader);
       if(fragShader.get() == NULL)
       {
           std::cerr<<"unnable to load vertex shader"<<std::endl;
       }
       program->addShader(fragShader);



       stateSet->setAttributeAndModes(program.get(), osg::StateAttribute::ON);
       stateSet->setMode(GL_DEPTH_TEST,osg::StateAttribute::ON);
       stateSet->setMode(GL_BLEND, osg::StateAttribute::ON);

  }

  osg::Group* createScene()
  {
      osg::ref_ptr<osg::Node> loadedModel = osgDB::readRefNodeFile("../vehicle1.stl");
      if(loadedModel == NULL)
      {
         std::cout<<"failed to load model";
         throw std::exception();
      }
      return dynamic_cast<osg::Group*>(loadedModel.release());
  }
