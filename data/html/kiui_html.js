HtmlLayer = Module.InkLayer.extend("InkLayer",
{
    move: function(index)
    {
    },
    show: function()
    {
    },
    hide: function()
    {
    },
});

HtmlInk = Module.Inkbox.extend("Inkbox",
{
    __construct: function(frame) {
        this.__parent.__construct.call(this, frame);
        this.element = $("<div></div>").appendTo("body");
		this.element.css({ 'position' : 'absolute', 'height' : 'auto', 'width' : 'auto' });
    },
    updateContent: function()
    {
		this.element.text(this.frame().widget().label());
    },
    updateFrame: function()
    {
        this.element.width(this.frame().cwidth());
        this.element.height(this.frame().cheight());
    },
    updateClip: function()
    {
    },
    updatePosition: function()
    {
		var aleft = this.frame().dabsolute(Module.Dimension.DIM_X) + this.frame().cleft();
		var atop = this.frame().dabsolute(Module.Dimension.DIM_Y) + this.frame().ctop();
        this.element.offset({ left: aleft, top : atop });
    },
    updateStyle: function()
    {
        var style = this.frame().inkstyle();
        if(style.image().name)
            this.element.css({ 'background-image' : 'url("/data/interface/uisprites/' + style.image().name + '.png"', 'background-size' : '100%' });
        if(style.backgroundColour().a() > 0.0)
            this.element.css({ 'background-color' : 'rgba(' + style.backgroundColour().r() + ',' + style.backgroundColour().g() + ',' + style.backgroundColour().b() + ',' + style.backgroundColour().a() + ')' });
    },
    show: function()
    {
        this.element.show();
    },
    hide: function()
    {
        this.element.hide();
    },
    contentSize: function(dim)
    {
		if(this.element.text())
			return (dim == Module.Dimension.DIM_X ? this.element.width() : this.element.height())
		return 0.0;
    },
	caretIndex: function(x, y)
    {
		return 0;
    },
	caretCoords: function(index, caretX, caretY, caretHeight)
    {
		
	},
});