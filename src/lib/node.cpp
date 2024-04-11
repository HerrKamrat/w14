#include "node.hpp"

#include <ranges>

void World::update(UpdateContext& context) {
    std::stable_sort(std::begin(m_nodes), std::end(m_nodes),
                     [](const std::unique_ptr<Node>& a, const std::unique_ptr<Node>& b) {
                         return a->getZIndex() < b->getZIndex();
                     });

    for (auto& node : m_nodes) {
        node->update(context);
    }
};

void World::render(RenderContext& context) {
    for (auto& node : m_nodes) {
        node->render(context);
    }
}

void World::onMouseButtonEvent(MouseButtonEvent& event) {
    for (auto it = m_nodes.rbegin(); it != m_nodes.rend(); it++) {
        (*it)->onMouseButtonEvent(event);
        if (event.isPropagationStopped()) {
            break;
        }
    }
};

void World::onMouseMotionEvent(MouseMotionEvent& event) {
    for (auto it = m_nodes.rbegin(); it != m_nodes.rend(); it++) {
        (*it)->onMouseMotionEvent(event);
        if (event.isPropagationStopped()) {
            break;
        }
    }
};

void World::addNode(std::unique_ptr<Node> node) {
    m_nodes.push_back(std::move(node));
}

void Node::initWithTextureRect(TextureRect textureRect) {
    setTextureRect(textureRect);
    setSize(textureRect.bounds.size);
};

void Node::update(UpdateContext& context){};

void Node::render(RenderContext& context) {
    // context.setColor({255, 255, 0, 125});
    // context.setTexture(nullptr);
    // context.drawRect(visualRect());
    // context.drawRect(m_contentRect);

    context.setColor(m_color);
    context.setTexture(getTexture());
    context.drawTexture(visualRect(), m_textureRect.bounds, m_angle);
    context.setColor({125, 255, 0});
    // context.drawRect(m_contentRect, true);
    context.setColor({0, 125, 255});
    // context.drawRect(visualRect(), true);
};

Rect Node::visualRect() {
    Size visualSize = m_contentRect.size * m_scale;
    Vec2 center = m_contentRect.center();
    Vec2 visualOrigin = center - (visualSize / 2.0).toVec2();
    return {visualOrigin, visualSize};
}
