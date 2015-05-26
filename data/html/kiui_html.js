mouseButton = function(event)
{
	if(event.which == 1)
		return Module.MouseButton.LEFT_BUTTON;
	else if(event.which == 2)
		return Module.MouseButton.MIDDLE_BUTTON;
	else if(event.which == 3)
		return Module.MouseButton.RIGHT_BUTTON;
}

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