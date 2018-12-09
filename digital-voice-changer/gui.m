function varargout = gui(varargin)

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @gui_OpeningFcn, ...
                   'gui_OutputFcn',  @gui_OutputFcn, ...
                   'gui_LayoutFcn',  [] , ...
                   'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
% End initialization code - DO NOT EDIT


% --- Executes just before gui is made visible.
function gui_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.


% Choose default command line output for gui
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes gui wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = gui_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);

varargout{1} = handles.output;


%���Ʋ���ͼ
function drawwave(handles)
global data newdata;
plot(handles.axes1,data);
plot(handles.axes2,newdata);

%����Ƶ��ͼ
function drawspectrum(handles)
global spectrum newspectrum;
plot(handles.axes1,abs(spectrum));
plot(handles.axes2,abs(newspectrum));


%������Ƶ   type��1Ϊ������2ΪŮ����3Ϊͯ��
function proc(handles,type)
global data newdata newspectrum fs;
if type==1
    newdata=ProcessVoice(data,fs,0.7,-200);
elseif type==2
    newdata=ProcessVoice(data,fs,2,200);
elseif type==3
    newdata=ProcessVoice(data,fs,3,400);
end
newspectrum=fft(newdata);
if get(handles.radiobutton1,'value')==1
    drawwave(handles);
else
    drawspectrum(handles);
end

%���ļ� ��ť
function pushbutton1_Callback(hObject, eventdata, handles)
global data fs;
global spectrum;
[openfilename,openfilepathname]=uigetfile('*.wav','����Ƶ�ļ�');
if ~(isequal(openfilename,0))
    [data,fs]=audioread(fullfile(openfilepathname,openfilename));
    spectrum=fft(data);
    set(handles.radiobutton1,'value',1);
    set(handles.radiobutton2,'value',0);
    drawwave(handles);
end





%¼�� ��ť
function pushbutton4_Callback(hObject, eventdata, handles)
global data fs;
global spectrum;

recorder=audiorecorder(40000,8,1);
set(handles.pushbutton4,'Enable','off');
set(handles.pushbutton4,'String','����¼��');
recordblocking(recorder,str2double(get(handles.edit1,'String')));
set(handles.pushbutton4,'Enable','on');
set(handles.pushbutton4,'String','¼��');
data=getaudiodata(recorder);
fs=40000;
spectrum=fft(data);
drawwave(handles);
set(handles.radiobutton1,'value',1);
set(handles.radiobutton2,'value',0);

%���� ��ť
function pushbutton5_Callback(hObject, eventdata, handles)
proc(handles,1);

%Ů�� ��ť
function pushbutton6_Callback(hObject, eventdata, handles)
proc(handles,2);

%ͯ�� ��ť
function pushbutton7_Callback(hObject, eventdata, handles)
proc(handles,3);

%�����ļ� ��ť
function pushbutton8_Callback(hObject, eventdata, handles)
global newdata fs;
[savefilename,savefilepathname]=uiputfile('*.wav','������Ƶ�ļ�');
if ~(isequal(savefilename,0))
    audiowrite(fullfile(savefilepathname,savefilename),newdata,fs);
end


%����ͼ ѡ��
function radiobutton1_Callback(hObject, eventdata, handles)
    set(hObject,'value',1);
    set(handles.radiobutton2,'value',0);
    drawwave(handles);


%Ƶ��ͼ ѡ��
function radiobutton2_Callback(hObject, eventdata, handles)
    set(hObject,'value',1);
    set(handles.radiobutton1,'value',0);
    drawspectrum(handles);

% ԭ���� ���� ��ť
function pushbutton9_Callback(hObject, eventdata, handles)
global data fs;
sound(data,fs);


% ������ ���� ��ť
function pushbutton10_Callback(hObject, eventdata, handles)
global newdata fs;
sound(newdata,fs);




function radiobutton1_CreateFcn(hObject, eventdata, handles)


function edit1_Callback(hObject, eventdata, handles)


% --- Executes during object creation, after setting all properties.
function edit1_CreateFcn(hObject, eventdata, handles)

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end
