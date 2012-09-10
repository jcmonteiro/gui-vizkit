#ifndef __VIZKIT_QVIZKITWIDGET__
#define __VIZKIT_QVIZKITWIDGET__

#include <vizkit/CompositeViewerQOSG.hpp>
#include <QtDesigner/QDesignerExportWidget>
#include <transformer/NonAligningTransformer.hpp>
#include <vizkit/Vizkit3DPlugin.hpp>

class ViewQOSG;
class QComboBox;
class QGroupBox;

namespace vizkit 
{
    class PickHandler;
    class CoordinateFrame;
    class GridNode;
    class QProperyBrowserWidget;

class QDESIGNER_WIDGET_EXPORT Vizkit3DWidget : public CompositeViewerQOSG 
{
    Q_OBJECT
    Q_PROPERTY(bool show_grid READ isGridEnabled WRITE setGridEnabled)
    Q_PROPERTY(bool show_axes READ areAxesEnabled WRITE setAxesEnabled)

public:
    Vizkit3DWidget( QWidget* parent = 0, Qt::WindowFlags f = 0 );
    
    /** Defined to avoid unnecessary dependencies in the headers
     *
     * If it is not defined explicitely, GCC will try to emit it inline, which
     * means that the types used in the osg_ptr below must be defined.
     */
    ~Vizkit3DWidget();

    osg::ref_ptr<osg::Group> getRootNode() const;
    osg::ref_ptr<ViewQOSG> getViewer();
    void addDataHandler(VizPluginBase *viz);
    void removeDataHandler(VizPluginBase *viz);
    
    /**
     * Sets the camera focus to specific position.
     * @param lookAtPos focus this point
     */
    void changeCameraView(const osg::Vec3& lookAtPos);
    /**
     * Sets the camera focus and the camera itself to specific position.
     * @param lookAtPos focus this point
     * @param eyePos position of the camera
     */
    void changeCameraView(const osg::Vec3& lookAtPos, const osg::Vec3& eyePos);
    void setTrackedNode( vizkit::VizPluginBase* plugin );

    QSize sizeHint() const;
    
public slots:
    void addPlugin(QObject* plugin, QObject* parent = NULL);
    void removePlugin(QObject* plugin);
    
    ///The frame in which the data should be displayed
    void setVizualisationFrame(const QString &frame);
    
    /**
     * Sets frame plugin data for a given plugin.
     * The pluging data frame is the frame in which the 
     * plugin expects the data to be.  
     * e.g. in case of the LaserScanVisualization 'laser'
     * */
    void setPluginDataFrame(const QString &frame, QObject *plugin);
    
    void pushDynamicTransformation(const base::samples::RigidBodyState &tr);
    void updateTransformations();
	
    /**
    * Function for adding static Transformations.
    * */
    void pushStaticTransformation(const base::samples::RigidBodyState &tr);

    QWidget* getPropertyWidget();

    void setCameraLookAt(double x, double y, double z);
    void setCameraEye(double x, double y, double z);
    void setCameraUp(double x, double y, double z);
        
signals:
    void addPlugins(QObject* plugin,QObject* parent);
    void removePlugins(QObject* plugin);
    void propertyChanged(QString propertyName);
    
private slots:
    void addPluginIntern(QObject* plugin,QObject *parent=NULL);
    void removePluginIntern(QObject* plugin);
    void pluginActivityChanged(bool enabled);

protected:
    void changeCameraView(const osg::Vec3* lookAtPos,
            const osg::Vec3* eyePos,
            const osg::Vec3* upVector);
    bool isGridEnabled();
    void setGridEnabled(bool enabled);
    bool areAxesEnabled();
    void setAxesEnabled(bool enabled);
    
    void checkAddFrame(const std::string &frame);

    osg::ref_ptr<osg::Group> root;
    void createSceneGraph();
    osg::ref_ptr<PickHandler> pickHandler;
    osg::ref_ptr<ViewQOSG> view;
    osg::ref_ptr<GridNode> groundGrid;
    osg::ref_ptr<CoordinateFrame> coordinateFrame;
    QStringList* pluginNames;
    QProperyBrowserWidget* propertyBrowserWidget;
    transformer::NonAligningTransformer transformer;
    QComboBox *frameSelector;
    QGroupBox* groupBox;
    
    std::string displayFrame;
    std::vector<VizPluginBase *> plugins;
 
    std::map<std::string, bool> availableFrames;
    
    /**
     * Book keeper class for the transfomrations
     * */
    class TransformationData
    {
        public:
	    TransformationData() : transformation(NULL) {};
            std::string dataFrame;
            transformer::Transformation *transformation;
    };
    
    std::map<vizkit::VizPluginBase*, TransformationData> pluginToTransformData;

    
};

}

#endif
