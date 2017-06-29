#ifndef TOYUI_TYPES_GEN_H
#define TOYUI_TYPES_GEN_H

#include <toyui/Config.h>
#include <toyui/Forward.h>

#include <toyobj/Type.h>

namespace toy
{   
    // Exported types
    template <> TOY_UI_EXPORT Type& typecls<Dimension>();
    template <> TOY_UI_EXPORT Type& typecls<Direction>();
    template <> TOY_UI_EXPORT Type& typecls<Pivot>();
    template <> TOY_UI_EXPORT Type& typecls<Align>();
    template <> TOY_UI_EXPORT Type& typecls<FrameType>();
    template <> TOY_UI_EXPORT Type& typecls<LayoutSolver>();
    template <> TOY_UI_EXPORT Type& typecls<AutoLayout>();
    template <> TOY_UI_EXPORT Type& typecls<Flow>();
    template <> TOY_UI_EXPORT Type& typecls<Sizing>();
    template <> TOY_UI_EXPORT Type& typecls<SpacePreset>();
    template <> TOY_UI_EXPORT Type& typecls<Clipping>();
    template <> TOY_UI_EXPORT Type& typecls<Opacity>();
    template <> TOY_UI_EXPORT Type& typecls<WidgetState>();
    template <> TOY_UI_EXPORT Type& typecls<std::vector<Widget*>>();
    
	template <> TOY_UI_EXPORT Type& typecls<MemberPointer<BoxFloat>>();
	template <> TOY_UI_EXPORT Type& typecls<MethodPointer<BoxFloat>>();
	template <> TOY_UI_EXPORT Type& typecls<MemberPointer<ImageSkin>>();
	template <> TOY_UI_EXPORT Type& typecls<MethodPointer<ImageSkin>>();
	template <> TOY_UI_EXPORT Type& typecls<MemberPointer<LayoutStyle>>();
	template <> TOY_UI_EXPORT Type& typecls<MethodPointer<LayoutStyle>>();
	template <> TOY_UI_EXPORT Type& typecls<MemberPointer<Style>>();
	template <> TOY_UI_EXPORT Type& typecls<MethodPointer<Style>>();
	template <> TOY_UI_EXPORT Type& typecls<MemberPointer<Widget>>();
	template <> TOY_UI_EXPORT Type& typecls<MethodPointer<Widget>>();
	template <> TOY_UI_EXPORT Type& typecls<MemberPointer<Wedge>>();
	template <> TOY_UI_EXPORT Type& typecls<MethodPointer<Wedge>>();
}

#endif // TOYUI_TYPES_GEN_H
