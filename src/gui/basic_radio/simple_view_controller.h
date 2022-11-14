#pragma once

#include <stdint.h>
#include <unordered_map>
#include <memory>

#include "imgui.h"
#include "texture.h"

#include "modules/dab/mot/MOT_entities.h"
#include "modules/dab/database/dab_database_entities.h"
#include "utility/span.h"

class Basic_Slideshow;
class BasicRadio;

struct SelectedSlideshowView {
    subchannel_id_t subchannel_id = 0;
    Basic_Slideshow* slideshow = NULL;
};

class SimpleViewController
{
private:
    std::unordered_map<uint32_t, std::unique_ptr<Texture>> textures;
    SelectedSlideshowView selected_slideshow;
public:
    service_id_t selected_service = 0;
    ImGuiTextFilter services_filter;
public:
    SimpleViewController() {}
    ~SimpleViewController();
    // Cannot move since we bind callbacks to this pointer
    SimpleViewController(SimpleViewController&) = delete;
    SimpleViewController(SimpleViewController&&) = delete;
    SimpleViewController& operator=(SimpleViewController&) = delete;
    SimpleViewController& operator=(SimpleViewController&&) = delete;

    void ClearSearch(void);
    Texture* GetTexture(subchannel_id_t subchannel_id, mot_transport_id_t transport_id);
    Texture* AddTexture(subchannel_id_t subchannel_id, mot_transport_id_t transport_id, tcb::span<const uint8_t> data);
    SelectedSlideshowView GetSelectedSlideshow();
    void SetSelectedSlideshow(SelectedSlideshowView _selected_slideshow);
    void AttachRadio(BasicRadio& radio);
private:
    uint32_t GetKey(subchannel_id_t subchannel_id, mot_transport_id_t transport_id) {
        return (subchannel_id << 16) | transport_id;
    }
};