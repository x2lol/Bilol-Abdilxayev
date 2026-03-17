const canvas = document.getElementById("canvas");
const ctx = canvas.getContext("2d");

const SIZE = 280;
const BRUSH_RADIUS = 12;

const TOUCH_OFFSET_X = -30;
const TOUCH_OFFSET_Y = -30;

let lastX = null;
let lastY = null;
let drawing = false;

/* configure drawing mode */

ctx.globalCompositeOperation = "lighter";
ctx.lineCap = "round";
ctx.lineJoin = "round";

/* utility functions */

function clamp(v, min, max){
    return Math.max(min, Math.min(max, v));
}

function getCanvasPosition(clientX, clientY){

    const rect = canvas.getBoundingClientRect();

    return {
        x: clientX - rect.left,
        y: clientY - rect.top
    };

}

/* drawing primitives */

function drawPoint(x,y){

    if(!Number.isFinite(x) || !Number.isFinite(y)) return;

    x = clamp(x,0,canvas.width);
    y = clamp(y,0,canvas.height);

    const gradient = ctx.createRadialGradient(
        x, y, 0,
        x, y, BRUSH_RADIUS
    );

    gradient.addColorStop(0,"rgba(255,255,255,1)");
    gradient.addColorStop(0.4,"rgba(255,255,255,0.6)");
    gradient.addColorStop(1,"rgba(255,255,255,0)");

    ctx.fillStyle = gradient;

    ctx.beginPath();
    ctx.arc(x,y,BRUSH_RADIUS,0,Math.PI*2);
    ctx.fill();
}

function drawLine(x,y){

    if(!Number.isFinite(x) || !Number.isFinite(y)) return;

    x = clamp(x,0,canvas.width);
    y = clamp(y,0,canvas.height);

    if(lastX === null){

        drawPoint(x,y);
        lastX = x;
        lastY = y;
        return;

    }

    const dx = x - lastX;
    const dy = y - lastY;

    const dist = Math.sqrt(dx*dx + dy*dy);

    const step = BRUSH_RADIUS * 0.6;
    const steps = Math.ceil(dist / step);

    for(let i=0;i<=steps;i++){

        const t = i / steps;

        const px = lastX + dx*t;
        const py = lastY + dy*t;

        drawPoint(px,py);

    }

    lastX = x;
    lastY = y;

}

/* mouse handlers */

canvas.addEventListener("mousedown",(e)=>{

    drawing = true;

    const pos = getCanvasPosition(e.clientX,e.clientY);

    drawLine(pos.x,pos.y);

});

window.addEventListener("mousemove",(e)=>{

    if(!drawing) return;

    const pos = getCanvasPosition(e.clientX,e.clientY);

    drawLine(pos.x,pos.y);

});

window.addEventListener("mouseup",()=>{

    drawing = false;
    lastX = null;
    lastY = null;

});

/* touch handlers */

canvas.addEventListener("touchstart",(e)=>{

    e.preventDefault();

    drawing = true;

    const touch = e.touches[0];

    const pos = getCanvasPosition(
        touch.clientX + TOUCH_OFFSET_X,
        touch.clientY + TOUCH_OFFSET_Y
    );

    drawLine(pos.x,pos.y);

});

canvas.addEventListener("touchmove",(e)=>{

    e.preventDefault();

    if(!drawing) return;

    const touch = e.touches[0];

    const pos = getCanvasPosition(
        touch.clientX + TOUCH_OFFSET_X,
        touch.clientY + TOUCH_OFFSET_Y
    );

    drawLine(pos.x,pos.y);

});

window.addEventListener("touchend",()=>{

    drawing = false;

    lastX = null;
    lastY = null;

});

/* canvas utilities */

function clearCanvas(){

    ctx.globalCompositeOperation = "source-over";

    ctx.clearRect(0,0,canvas.width,canvas.height);

    ctx.globalCompositeOperation = "lighter";

    lastX = null;
    lastY = null;

}

/* pixel extraction */

function extractPixels(){

    const image = ctx.getImageData(0,0,SIZE,SIZE);
    const data = image.data;

    const pixels = [];

    for(let i = 0; i < data.length; i+= 4){

        const r = data[i];
        const g = data[i+1];
        const b = data[i+2];

        const intensity = (r + g + b) / 3;

        pixels.push(intensity / 255);

    }

    return pixels;

}