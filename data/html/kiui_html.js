mouseButton = function(event)
{
	if(event.which == 1)
		return Module.MouseButton.LEFT_BUTTON;
	else if(event.which == 2)
		return Module.MouseButton.MIDDLE_BUTTON;
	else if(event.which == 3)
		return Module.MouseButton.RIGHT_BUTTON;
}

html_ink_global_id = 0;

HtmlTarget = Module.InkTarget.extend('InkTarget',
{
	__construct: function(layers, width, height, uiWindow)
	{
		this.__parent.__construct.call(this, layers);
		this.uiWindow = uiWindow;
		this.element = $('<div id="main_target"></div>').appendTo('.emscripten_border');
		this.element.css({ 'position' : 'relative', 'width' : width + 'px', 'height' : height + 'px', 'background-color' : 'rgb(0,0,0)' });
		var target = this.element;
		this.element.on('mousedown', function(event) {
			uiWindow.dispatchMousePressed(event.pageX - $(target).offset().left, event.pageY - $(target).offset().top, mouseButton(event));
			return false;
		});
		this.element.on('mouseup', function(event) {
			uiWindow.dispatchMouseReleased(event.pageX - $(target).offset().left, event.pageY - $(target).offset().top, mouseButton(event));
			return false;
		});
		this.element.on('mousemove', function(event) {
			uiWindow.dispatchMouseMoved(event.pageX - $(target).offset().left, event.pageY - $(target).offset().top, 0.0, 0.0);
			return false;
		});
		$('#canvas').css('display', 'none');
	},
});

HtmlLayer = Module.InkLayer.extend('InkLayer',
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

TextSizer = document.createElement('div');
document.body.appendChild(TextSizer);
TextSizer.style.cssText = 'position:absolute; height:auto; width:auto; white-space:nowrap;';

ImgSizer = document.createElement('img');
document.body.appendChild(ImgSizer);
			
HtmlInk = Module.HtmlInkImpl.extend('HtmlInkImpl',
{
    __construct: function(frame)
	{
		this.widget = frame.widget();
		this.parent = frame.parent();
		this.parentbox = this.parent ? this.parent.inkbox() : 0;
		
        this.element = document.createElement('div');
		this.element.id = ++html_ink_global_id;
		if(this.parent)
			this.parentbox.element.appendChild(this.element);
		else
			document.getElementById('main_target').appendChild(this.element);
		
		this.__parent.__construct.call(this, frame, this.element);
    },
	__destruct: function(frame)
	{
		this.__parent.__destruct.call(this);
		this.element.parentNode.removeChild(this.element);
	},
	styleCSS: function(name, css)
	{
		if(!document.getElementById(name))
		{
			var style = document.createElement('style');
			style.id = name;
			style.type = 'text/css';
			style.innerHTML = '.' + name + ' { ' + css + ' }';
			document.head.appendChild(style);
		}
		
		this.element.className = name;
	},
	elementCSS: function(css)
	{
		this.element.style.cssText = 'position:absolute;';
		this.element.style.cssText += css;
	},
    updateContent: function()
    {
		if(this.widget.label())
			this.element.textContent = this.widget.label();
    },
    contentSize: function(dim)
    {		
		if(this.element.textContent)
		{
			TextSizer.style.font = this.element.style.font;
			TextSizer.textContent = this.element.textContent;
			return (dim == Module.Dimension.DIM_X ? TextSizer.clientWidth : TextSizer.clientHeight);
		}
		else if(this.widget.image())
		{
			ImgSizer.src = 'data/interface/uisprites/' + this.widget.image().name + '.png';
			return (dim == Module.Dimension.DIM_X ? ImgSizer.naturalWidth : ImgSizer.naturalHeight);
		}
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