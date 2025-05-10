#include "object_affiliate.h"

void ObjectAffiliate::setOffsetByAnchor(Anchor &anchhor) {
  anchor_ = anchhor;
  switch(anchhor){
    // **这就是锚点（想想再现实中锚点的作用）***/
    //*******************-*-顶-部-*-********************************************** */
    case Anchor::TOP_LEFT:
    offset_ = glm::vec2(0.0f, 0.0f);
    break;
    case Anchor::TOP_CENTER:
    offset_ = glm::vec2(-size_.x / 2.0f, 0.0f);
    break;
    case Anchor::TOP_RIGHT:
    offset_ = glm::vec2(-size_.x, 0.0f);
    break;
    //******************-*-中-间-*-**************************************** */
    case Anchor::CENTER_LEFT:
    offset_ = glm::vec2(0.0f, -size_.y / 2.0f);
    break;
    case Anchor::CENTER:
    offset_ = glm::vec2(-size_.x / 2.0f, -size_.y / 2.0f);
    break;
    case Anchor::CENTER_RIGHT:
    offset_ = glm::vec2(-size_.x, -size_.y / 2.0f);
    break;
    //*******************-*-底-部-*-*********************************** */ */
    case Anchor::BOTTOM_LEFT:
    offset_ = glm::vec2(0.0f, -size_.y);
    break;
    case Anchor::BOTTOM_CENTER:
    offset_ = glm::vec2(-size_.x / 2.0f, -size_.y);
    break;
    case Anchor::BOTTOM_RIGHT:
    offset_ = glm::vec2(-size_.x, -size_.y);
    break;

  }
}

void ObjectAffiliate::setSize(const glm::vec2 size) {
  size_ = size;
  setOffsetByAnchor(anchor_);
}

void ObjectAffiliate::setScale(float scale) {
  size_ *= scale;
  setOffsetByAnchor(anchor_);
}
