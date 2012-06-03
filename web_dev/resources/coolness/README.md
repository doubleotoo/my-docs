web_dev > resources > coolness
==============================

#### [Yahoo! datatables.org](http://www.datatables.org/)
* Uses awesome icons from [The Noun Project](http://thenounproject.com/)
* Nice blue theme

  light fuzzy blue:
    background-color: #F4FAFD;

  light soft blue:
    color: #8AABC3;

  dark navy blue:
    color: #004173;

  dark navy blue:
    color: #454545;


Edit pictures in browser: http://pixlr.com/

Google: edit-svg

Interact with SVG in HTML
  http://blogs.igalia.com/eocanha/2008/11/03/how-to-interact-with-an-svg-image-from-an-html-document/

JQuery SVG
http://keith-wood.name/svg.html

SVG DOM

## Change SVG color

1. Open svg file in text editor to see HTML
2. Use jquery selector to select desired group `<g>`
3. Change color: `svg.style('#group1 {fill: black}');`
3. Change all groups color: `svg.style('g {fill: black}');`


http://stackoverflow.com/questions/5369992/animating-externally-loaded-svg-with-keith-woods-jquery-svg-plugin

I'm trying to animate the fill color of a group of path's loaded from an external SVG using Keith Wood's plugin.

First I import the SVG into a div container:

$(document).ready(function() {
$('#header-main').svg({loadURL: 'header.svg'});
var svg = $('#header-main').svg('get');

});

The SVG file looks like this:

<svg>
  <g id="group1">
    <path d="M0,22.943V0.223h1.413v22.721H0z"/>
    <path etc../>
  </g>
</svg>

I can change the fill color of the group or individual paths like so:

svg.style('#group1 {fill: black}');

Now when I try to animate the paths like this:

$('path').animate({svgFill: 'blue'}, 500);

or $('#group1').animate({svgFill: 'blue'}, 500);

or with any other selector, for instance the id of a path, nothing happens. But if I were to create a path, and animate it like this:

    var path1 = svg.createPath(); 
svg.path(path1.move(50, 90).curveC(0, 90, 0, 30, 50, 30). 
    line(150, 30).curveC(200, 30, 200, 90, 150, 90).close(),  
    {fill: 'none', stroke: '#D90000', strokeWidth: 10});
$('path').animate({svgFill: 'blue'}, 500);

the path I created animates, but the other paths that were imported from header.svg file do nothing.

Am I doing something wrong here, or is the plugin just not capable of animating external svg?

