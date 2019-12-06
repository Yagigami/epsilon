#include <kandinsky/context.h>
#include <stdio.h>

void KDContext::updateImage(KDPoint p, KDPoint oldp, KDImage const *const spt, KDColor background) {
  fillRect(KDRect(oldp, spt->m_size), background);
  fillRectWithPixels(KDRect(p, spt->m_size), spt->m_img, nullptr);
}

void KDContext::updateAnim(KDPoint p, KDPoint oldp, KDAnimation const *const anim, KDColor background) {
  fillRect(KDRect(oldp, anim->m_size), background);
  fillRectWithPixels(KDRect(p, anim->m_size), anim->m_anim + anim->m_currentFrame * anim->m_width * anim->m_height, nullptr);
}
