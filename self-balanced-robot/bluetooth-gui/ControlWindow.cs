using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Imaging;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace pinghengxiaoche {

 


    public partial class ControlWindow : Form {

        ControlBar ControlBarInstance;

        bool Resizing = false;


        public ControlWindow()
        {
            InitializeComponent();
        }


        private void ControlWindow_Load(object sender, EventArgs e)
        {
            ControlBarInstance = new ControlBar(pictureBox1, 30, 30, imageList1.Images[0], imageList1.Images[2], imageList1.Images[1], ButtonMoveCallBack);
        }


        private void ButtonMoveCallBack(PointF NormalizedPosition)
        {

        }

        private void ControlWindow_ResizeEnd(object sender, EventArgs e)
        {
            ControlBarInstance.init(pictureBox1, 30, 30, imageList1.Images[0], imageList1.Images[2], imageList1.Images[1], ButtonMoveCallBack);
            Resizing = false;
        }

        private void ControlWindow_ResizeBegin(object sender, EventArgs e)
        {
            Resizing = true;
        }

        private void ControlWindow_SizeChanged(object sender, EventArgs e)
        {
            if (!Resizing) {
                ControlBarInstance.init(pictureBox1, 30, 30, imageList1.Images[0], imageList1.Images[2], imageList1.Images[1], ButtonMoveCallBack);
            }

        }


    }







    public class ControlBar {
        private PictureBox PictureBoxControl;
        private int ButtonHeight, ButtonWidth;
        private int HalfButtonHeight, HalfButtonWidth;
        private Point Center;
        private Point _ButtonCenter = new Point(0, 0);
        private Point FormerButtonCenter;
        private Point ButtonCenter
        {
            get {
                return _ButtonCenter;
            }
            set {
                FormerButtonCenter.X = ButtonCenter.X;
                FormerButtonCenter.Y = ButtonCenter.Y;
                _ButtonCenter = value;
                ButtonMoveCallBack?.Invoke(value);
            }
        }
        private Point MouseButtonCenterDelta;            //鼠标坐标减按钮中心坐标  （当鼠标没有点在按钮正中心时，保存其偏差）
        private Image ImgDefault;
        private Image ImgHighLight;
        private Image ImgPressDown;
        private Graphics PictureBoxControlGraphics;
        private Graphics BufferGraphics;

        private Action<PointF> ButtonMoveCallBack;    //只要按钮位置一变（鼠标引起的或程序引起的）就会调用

        private bool ButtonDown = false;
        private bool MouseInButton = false;

        private Brush BackgroundBrush;
        private Bitmap Buffer;                       //双缓冲


        public void init(PictureBox pictureboxcontrol, int buttonheight, int buttonwidth, Image imgdefault, Image imghighlight, Image imgpressdown, Action<PointF> buttonmovecallback)
        {
            PictureBoxControl = pictureboxcontrol;
            ButtonHeight = buttonheight;
            ButtonWidth = buttonwidth;
            HalfButtonHeight = ButtonHeight / 2;
            HalfButtonWidth = ButtonWidth / 2;
            ImgDefault = imgdefault;
            ImgHighLight = imghighlight;
            ImgPressDown = imgpressdown;
            Center = new Point(pictureboxcontrol.Width / 2, pictureboxcontrol.Height / 2);
            ButtonCenter = new Point(0, 0);
            MouseButtonCenterDelta = new Point(0, 0);
            SetButtonPosition(Center.X, Center.Y);
            Buffer = new Bitmap(PictureBoxControl.Width, PictureBoxControl.Height);
            BufferGraphics = Graphics.FromImage(Buffer);

            ButtonMoveCallBack = buttonmovecallback;
            PictureBoxControlGraphics = PictureBoxControl.CreateGraphics();
            BackgroundBrush = new SolidBrush(PictureBoxControl.BackColor);

            ButtonDown = false;
            MouseInButton = false;

            PictureBoxControl.MouseDown += new MouseEventHandler(OnMouseDown);
            PictureBoxControl.MouseUp += new MouseEventHandler(OnMouseUp);
            PictureBoxControl.MouseMove += new MouseEventHandler(OnMouseMove);
            PictureBoxControl.Paint += new PaintEventHandler(OnPaint);

            

            Paint(PictureBoxControlGraphics);
            PictureBoxControl.Refresh();

        }

        public ControlBar(PictureBox pictureboxcontrol, int buttonheight, int buttonwidth, Image imgdefault, Image imghighlight, Image imgpressdown, Action<PointF> buttonmovecallback)
        {
            init(pictureboxcontrol, buttonheight, buttonwidth, imgdefault, imghighlight, imgpressdown, buttonmovecallback);
        }

        public ControlBar() {; }

        private Point BorderCheck(int x, int y)             //按钮中心位置的边界检查，超出边界时值为边界
        {
            Point ret = new Point();

            if (x < HalfButtonWidth) ret.X = HalfButtonWidth;
            else if (x > PictureBoxControl.Width - HalfButtonWidth - 2) ret.X = PictureBoxControl.Width - HalfButtonWidth - 2;
            else ret.X = x;

            if (y < HalfButtonHeight) ret.Y = HalfButtonHeight;
            else if (y > PictureBoxControl.Height - HalfButtonHeight - 2) ret.Y = PictureBoxControl.Height - HalfButtonHeight - 2;
            else ret.Y = y;

            return ret;
        }

        private bool IsMouseInButton(int x,int y)
        {
            if (
                x >= ButtonCenter.X - HalfButtonWidth &&
                x <= ButtonCenter.X + HalfButtonWidth &&
                y >= ButtonCenter.Y - HalfButtonHeight &&
                y <= ButtonCenter.Y + HalfButtonHeight
            ) {
                return true;
            }
            else {
                return false;
            }

        }

        private void Paint(Graphics g)
        {

            ////未用双缓冲技术，按钮会闪动。
            //if (ButtonDown) {
            //    g.FillRectangle(BackgroundBrush, FormerButtonCenter.X - HalfButtonWidth, FormerButtonCenter.Y - HalfButtonHeight, ButtonWidth, ButtonHeight);
            //    g.DrawImage(ImgPressDown, ButtonCenter.X - HalfButtonWidth, ButtonCenter.Y - HalfButtonHeight, ButtonWidth, ButtonHeight);
            //    return;
            //}
            //else if (MouseInButton) {

            //    g.DrawImage(ImgHighLight, ButtonCenter.X - HalfButtonWidth, ButtonCenter.Y - HalfButtonHeight, ButtonWidth, ButtonHeight);
            //    return;
            //}
            //else {

            //    g.DrawImage(ImgDefault, ButtonCenter.X - HalfButtonWidth, ButtonCenter.Y - HalfButtonHeight, ButtonWidth, ButtonHeight);
            //    return;
            //}

            
            //使用双环从技术，按钮拖动起来平滑顺畅。
            Rectangle EraseRect = new Rectangle(FormerButtonCenter.X - HalfButtonWidth, FormerButtonCenter.Y - HalfButtonHeight, ButtonWidth, ButtonHeight);  //擦除部分
            Rectangle ButtonRect = new Rectangle(ButtonCenter.X - HalfButtonWidth, ButtonCenter.Y - HalfButtonHeight, ButtonWidth, ButtonHeight);             //重绘部分

            if (ButtonDown) {  //按钮正在拖动
                BufferGraphics.FillRectangle(BackgroundBrush, EraseRect);
                BufferGraphics.DrawImage(ImgPressDown, ButtonRect);
                g.DrawImage(Buffer, EraseRect.X, EraseRect.Y, EraseRect, GraphicsUnit.Pixel);
                g.DrawImage(Buffer, ButtonRect.X, ButtonRect.Y, ButtonRect, GraphicsUnit.Pixel);

                return;
            }
            else if (MouseInButton) {  //鼠标悬停在按钮上
                BufferGraphics.FillRectangle(BackgroundBrush, EraseRect);
                BufferGraphics.DrawImage(ImgHighLight, ButtonRect);
                g.DrawImage(Buffer, EraseRect.X, EraseRect.Y, EraseRect, GraphicsUnit.Pixel);
                g.DrawImage(Buffer, ButtonRect.X, ButtonRect.Y, ButtonRect, GraphicsUnit.Pixel);
                return;
            }
            else {                     //按钮的默认样式
                BufferGraphics.FillRectangle(BackgroundBrush, EraseRect);
                BufferGraphics.DrawImage(ImgDefault, ButtonRect);
                g.DrawImage(Buffer, EraseRect.X, EraseRect.Y, EraseRect, GraphicsUnit.Pixel);
                g.DrawImage(Buffer, ButtonRect.X, ButtonRect.Y, ButtonRect, GraphicsUnit.Pixel);
                return;
            }
        }

        public PointF GetNormalizedPosition()
        {
            PointF ret = new PointF();
            ret.X = (float)(ButtonCenter.X - Center.X) / (float)(PictureBoxControl.Width - ButtonWidth) / 2F;
            ret.Y = (float)(ButtonCenter.Y - Center.Y) / (float)(PictureBoxControl.Height - ButtonHeight) / 2F;
            return ret;
        }

        public void SetButtonPosition(int x, int y)      //按钮 中心位置
        {
            ButtonCenter = BorderCheck(x, y);
        }
        

        private void OnMouseDown(object sender, MouseEventArgs e)
        {
            if (IsMouseInButton(e.X, e.Y)) {
                MouseInButton = true;
                ButtonDown = true;
                MouseButtonCenterDelta.X = e.X - ButtonCenter.X;
                MouseButtonCenterDelta.Y = e.Y - ButtonCenter.Y;
                Paint(PictureBoxControlGraphics);

            }
        }

        private void OnMouseUp(object sender, MouseEventArgs e)
        {
            ButtonDown = false;
            if (IsMouseInButton(e.X, e.Y)) {
                MouseInButton = true;
            }
            else {
                MouseInButton = false;
            }
            SetButtonPosition(Center.X, Center.Y);
            
            Paint(PictureBoxControlGraphics);
        }

        private void OnMouseMove(object sender, MouseEventArgs e)
        {
            if (!ButtonDown) {                         //按钮没有按下
                if (IsMouseInButton(e.X, e.Y)) {
                    MouseInButton = true;
                    Paint(PictureBoxControlGraphics);

                }
                else {
                    MouseInButton = false;
                    Paint(PictureBoxControlGraphics);
                }
            }
            else {                                      //按钮按下
                SetButtonPosition(e.X - MouseButtonCenterDelta.X, e.Y - MouseButtonCenterDelta.Y);
                Paint(PictureBoxControlGraphics);
            }
        }

        private void OnPaint(object sender, PaintEventArgs e)
        {
            Paint(e.Graphics);
        }


    }

    
}
