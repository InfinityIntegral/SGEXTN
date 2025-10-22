#ifndef SGRRENDERERNODE_H
#define SGRRENDERERNODE_H

#include <QSGRenderNode>
#include <QByteArray>

class RenderState;
class SGRBaseRenderer;
class QRhi;
class QQuickItem;
class SGRRenderingProgramme;
class SGRRendererNode : public QSGRenderNode
{
public:
    SGRRendererNode(SGRBaseRenderer* renderControl);
    SGRRendererNode(const SGRRendererNode&) = delete;
    SGRRendererNode& operator=(const SGRRendererNode&) = delete;
    SGRRendererNode(SGRRendererNode&& x) = delete;
    SGRRendererNode& operator=(SGRRendererNode&& x) = delete;
    ~SGRRendererNode();
    void prepare() override;
    void render(const RenderState* /*unused*/) override;
    void releaseResources() override;
    RenderingFlags flags() const override;
    QSGRenderNode::StateFlags changedStates() const override;
    QQuickItem* associatedItem;
    SGRBaseRenderer* renderControl;
    QRhi* rhi;
    SGRRenderingProgramme* renderingProgramme;
};

#endif // SGRRENDERERNODE_H
