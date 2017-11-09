#ifndef TOYUI_TYPES_GEN_H
#define TOYUI_TYPES_GEN_H

#include <toyui/Config.h>
#include <toyui/Forward.h>

#include <toyobj/Type.h>

namespace toy
{   
    // Exported types
    template <> TOY_UI_EXPORT Type& cls<Dimension>();
    template <> TOY_UI_EXPORT Type& cls<Direction>();
    template <> TOY_UI_EXPORT Type& cls<Pivot>();
    template <> TOY_UI_EXPORT Type& cls<Align>();
    template <> TOY_UI_EXPORT Type& cls<FrameType>();
    template <> TOY_UI_EXPORT Type& cls<LayoutSolver>();
    template <> TOY_UI_EXPORT Type& cls<AutoLayout>();
    template <> TOY_UI_EXPORT Type& cls<Flow>();
    template <> TOY_UI_EXPORT Type& cls<Sizing>();
    template <> TOY_UI_EXPORT Type& cls<SpacePreset>();
    template <> TOY_UI_EXPORT Type& cls<Clipping>();
    template <> TOY_UI_EXPORT Type& cls<Opacity>();
    template <> TOY_UI_EXPORT Type& cls<WidgetState>();
    template <> TOY_UI_EXPORT Type& cls<std::vector<Widget*>>();
    
	template <> TOY_UI_EXPORT Type& cls<MemberPointer<ImageSkin>>();
	template <> TOY_UI_EXPORT Type& cls<MethodPointer<ImageSkin>>();
	template <> TOY_UI_EXPORT Type& cls<MemberPointer<LayoutStyle>>();
	template <> TOY_UI_EXPORT Type& cls<MethodPointer<LayoutStyle>>();
	template <> TOY_UI_EXPORT Type& cls<MemberPointer<Style>>();
	template <> TOY_UI_EXPORT Type& cls<MethodPointer<Style>>();
	template <> TOY_UI_EXPORT Type& cls<MemberPointer<Widget>>();
	template <> TOY_UI_EXPORT Type& cls<MethodPointer<Widget>>();
	template <> TOY_UI_EXPORT Type& cls<MemberPointer<Wedge>>();
	template <> TOY_UI_EXPORT Type& cls<MethodPointer<Wedge>>();
}

#endif // TOYUI_TYPES_GEN_H
