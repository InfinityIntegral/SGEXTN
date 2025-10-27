#ifndef SGRRENDERERNODE_H
#define SGRRENDERERNODE_H

#include <QSGRenderNode>
#include <QRectF>

class RenderState;
class SGRBaseRenderer;
class QRhi;
class QQuickItem;
class SGRRenderingProgramme;
class SGRBaseSyncer;
class SGRRendererNode : public QSGRenderNode
{
public:
    SGRRendererNode(SGRBaseRenderer* renderControl);
    SGRRendererNode(const SGRRendererNode&) = delete;
    SGRRendererNode& operator=(const SGRRendererNode&) = delete;
    SGRRendererNode(SGRRendererNode&& x) = delete;
    SGRRendererNode& operator=(SGRRendererNode&& x) = delete;
    ~SGRRendererNode() override;
    void prepare() override;
    void render(const RenderState* /*unused*/) override;
    void releaseResources() override;
    [[nodiscard]] RenderingFlags flags() const override;
    [[nodiscard]] QSGRenderNode::StateFlags changedStates() const override;
    [[nodiscard]] QRectF rect() const override;
    SGRBaseRenderer* renderControl;
    QRhi* rhi;
    SGRRenderingProgramme* renderingProgramme;
    SGRBaseRenderer* rendererToDelete;
    SGRBaseSyncer* syncerToDelete;
};

#endif // SGRRENDERERNODE_H
