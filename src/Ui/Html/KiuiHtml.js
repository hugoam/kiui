var HtmlWindow = Module.Interface.extend("HtmlWindowProxy",
{
    __construct: function() {
        this.__parent.__construct.call(this);
        this.target = new HtmlTarget();
        
        $(document).bind('click', function(event)
        {

        });
    },
    screenTarget: function()
    {
        return this.target;
    },
});

var HtmlTarget = Module.Interface.extend("HtmlTargetProxy",
{
    createLayer: function(layer, index)
    {
        return new HtmlLayer(layer, this, index);
    },
});

var HtmlLayer = Module.Interface.extend("HtmlLayerProxy",
{
    createInkbox: function(frame)
    {
        return new HtmlInk(frame);
    },
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

var HtmlInk = Module.Interface.extend("HtmlInkProxy",
{
    __construct: function(frame) {
        this.__parent.__construct.call(this, frame);
        this.element = $(document).append('<div></div>')
    },
    updateContent: function()
    {
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
        this.element.position(this.frame().cleft(), this.frame().ctop());
    },
    updateStyle: function()
    {
        var style = this.frame().inkstyle();
        if(style.image().name)
            this.element.css({ 'background-image' : 'url(\'' + MonkDraw.imageroot + $(image).attr('image') + '.png\'', 'background-size' : '100%' });
        if(style.backgroundColour().a() > 0)
            this.element.css({ 'background-colour' : 'rgba(' + style.backgroundColour().r() + ',' + style.backgroundColour().g() + ',' + style.backgroundColour().b() + ',' + style.backgroundColour().a() + ')'
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
    },
	caretIndex: function(x, y)
    {
    },
	caretCoords: function(index, caretX, caretY, caretHeight)
    {
    },
});