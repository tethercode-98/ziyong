#ifndef OBJECT_AFFILIATE_H
#define OBJECT_AFFILIATE_H

#include "object_screen.h"

class ObjectAffiliate : public Object {
protected:
    ObjectScreen * parrent_ = nullptr; // 父节点
    glm::vec2 offset_ = glm::vec2(0, 0); // 相对父节点偏移量
    glm::vec2 size_ = glm::vec2(0, 0); // 大小
    Anchor anchor_ = Anchor::CENTER; // 锚点 // 再没有合并之前可以随便设，合并后需要中间
public:
    void setOffsetByAnchor(Anchor &anchhor);

    // ***********************************************************/* */   getters and setters
    //************************成员：parrent_ 的 获取与修改*********** */
    ObjectScreen* getParent() const { return parrent_; };        /* */
    void setParent(ObjectScreen *parent) { parrent_ = parent; }; /* */

    //************************成员：offset_ 的 获取与修改************ */
    glm::vec2 getOffset() { return offset_; };                   /* */
    void setOffset(glm::vec2 offset) { offset_ = offset; };      /* */

    //************************成员：size_ 的 获取与修改************* */
    glm::vec2 getSize() const { return size_; };                /* */
    void setSize(const glm::vec2 size);                         /* */

    void setScale(float scale); // 缩放 

    //************************成员：anchor_ 的 获取与修改*********** */
    Anchor getAnchor() const { return anchor_; };               /* */
    void setAnchor(Anchor anchor) { anchor_ = anchor; };        /* */
};  

#endif