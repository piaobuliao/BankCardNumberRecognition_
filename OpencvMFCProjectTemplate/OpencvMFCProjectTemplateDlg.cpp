
// OpencvMFCProjectTemplateDlg.cpp : implementation file
//

#include "stdafx.h"
#include "OpencvMFCProjectTemplate.h"
#include "OpencvMFCProjectTemplateDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
   
#include <opencv2/imgproc/imgproc.hpp>  
#include <opencv2/core/core.hpp>        
#include <opencv2/highgui/highgui.hpp>   
#include <opencv2/features2d/features2d.hpp>
#include "opencv2/objdetect/objdetect.hpp"

#include "svm.h"
#include "svmex.h"


 
#define M_PI 3.14159265358979323846

using namespace std;
using namespace cv;

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// COpencvMFCProjectTemplateDlg dialog




COpencvMFCProjectTemplateDlg::COpencvMFCProjectTemplateDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(COpencvMFCProjectTemplateDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void COpencvMFCProjectTemplateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(COpencvMFCProjectTemplateDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_Test, &COpencvMFCProjectTemplateDlg::OnBnClickedTest)
	ON_BN_CLICKED(IDC_BUTTON_HoGTest, &COpencvMFCProjectTemplateDlg::OnBnClickedButtonHogtest)
	ON_BN_CLICKED(IDC_BUTTON_SaveHogToTxt, &COpencvMFCProjectTemplateDlg::OnBnClickedButtonSavehogtotxt)
	ON_BN_CLICKED(IDC_BUTTON_MergeHogFeatures, &COpencvMFCProjectTemplateDlg::OnBnClickedButtonMergehogfeatures)
	ON_BN_CLICKED(IDC_BUTTON_ReadImageAndNumRecognition, &COpencvMFCProjectTemplateDlg::OnBnClickedButtonReadimageandnumrecognition)
	ON_BN_CLICKED(IDC_BUTTON_DealWithCuttedNum, &COpencvMFCProjectTemplateDlg::OnBnClickedButtonDealwithcuttednum)
	ON_BN_CLICKED(IDC_BUTTON_DealWithMNIST, &COpencvMFCProjectTemplateDlg::OnBnClickedButtonDealwithmnist)
	ON_BN_CLICKED(IDC_BUTTON_BankCardNumRecognition, &COpencvMFCProjectTemplateDlg::OnBnClickedButtonBankcardnumrecognition)
END_MESSAGE_MAP()


// COpencvMFCProjectTemplateDlg message handlers

BOOL COpencvMFCProjectTemplateDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void COpencvMFCProjectTemplateDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void COpencvMFCProjectTemplateDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR COpencvMFCProjectTemplateDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//把提取的数字缩放到28*28尺寸   数字图像最长的边缩放到28，
int rePlaceTheNum()
{
	return 0;
}

///sortBoundingRectsBy XPosition of boundingRectsForContour
int sortBoundingRectsByPosition(vector<Rect> &boundingRectsForContour)
{
	vector<Rect> boundingRectsClone;
	vector<int >  boundingRectsXPosition;
	boundingRectsClone.resize(boundingRectsForContour.size());
	boundingRectsXPosition.resize(boundingRectsForContour.size());

	// copy the data of boundingRectsForContour
	for (int i=0; i<boundingRectsForContour.size(); i++)
	{		
		boundingRectsClone[i] = boundingRectsForContour[i];
		boundingRectsXPosition[i] =  boundingRectsForContour[i].x; 
	}
	sort(boundingRectsXPosition.begin() , boundingRectsXPosition.end()); 

	//boundingRectsXPosition 已经排序了的，so。。。根据它从boundingRectsClone复制。。存到boundingRectsForContour
	for (int i=0; i<boundingRectsForContour.size(); i++)
	{	
		for (int j=0; j<boundingRectsClone.size(); j++)
		{
			if ( boundingRectsClone[j].x == boundingRectsXPosition[i])
			{
				boundingRectsForContour[i] = boundingRectsClone[j];
			}
		}
	}

	return 0;

}

/// binaryImage：二值图
/// boundingRectsForContour：按x坐标排序的每个字符轮廓的外界矩形
int separateNumsByContour(Mat binaryImage,vector<Rect> &boundingRectsForContour)
{

#pragma region detect Contour
	vector< vector<Point> > filterContours;
	vector< vector<Point> > contours;   // 轮廓     
	//vector< vector<Point> > filterContours; // 筛选后的轮廓  
	vector< Vec4i > hierarchy;    // 轮廓的结构信息   
	contours.clear();    
	hierarchy.clear();   
	filterContours.clear();  

	findContours(binaryImage, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);    

	// 去除伪轮廓: 轮廓上像素点数太少的 
	for (size_t i = 0; i < contours.size(); i++)   
	{  
		if (fabs(contourArea(Mat(contours[i]))) > 20)
			filterContours.push_back(contours[i]);  
	}  

	binaryImage.setTo(0);  
	drawContours(binaryImage, filterContours, -1, Scalar(255,255,255), -1); //8, hierarchy); 
	imshow("coutour filled",binaryImage);

#pragma endregion detect Contour


#pragma region calculate Bounding Rect and sort it
	//vector<Rect> boundingRectsForContour;
	vector<int >  boundingRectsXPosition;
	boundingRectsForContour.resize(filterContours.size());
	boundingRectsXPosition.resize(filterContours.size());

	for (int i=0; i<filterContours.size(); i++)
	{
		boundingRectsForContour[i] = boundingRect(filterContours[i]);
		boundingRectsXPosition[i] =  boundingRectsForContour[i].x;
		rectangle(binaryImage,boundingRectsForContour[i],Scalar(255, 0, 255));
		
	}
	imshow("coutour filled with BoundingRect",binaryImage);

	///sortBoundingRectsBy XPosition of boundingRectsForContour
	sortBoundingRectsByPosition(boundingRectsForContour); 

	
		
#pragma endregion calculate Bounding Rect and sort it


	

	return 0;

}

// if the x position of two rects is too nearby..merge them
// if the width of rect is too large , separate them
int fineSeparateByContourAnalyse(vector<Rect> &coarseBoundingRects,vector<Rect> &fineBoundingRects)
{
	int medianRectWidth=0;

	//find the median width of the rect
#if 1

	vector<Rect> boundingRectsClone;
	vector<int >  boundingRectsWidth;
	boundingRectsClone.resize(coarseBoundingRects.size());
	boundingRectsWidth.resize(coarseBoundingRects.size());

	// copy the data of boundingRectsForContour
	for (int i=0; i<coarseBoundingRects.size(); i++)
	{		
		boundingRectsClone[i] = coarseBoundingRects[i];
		boundingRectsWidth[i] =  coarseBoundingRects[i].width; 
	}
	sort(boundingRectsWidth.begin() , boundingRectsWidth.end()); 
		 

	if ( (boundingRectsWidth.size() % 2 ) == 0)
	{
		medianRectWidth = boundingRectsWidth[boundingRectsWidth.size()/2] + boundingRectsWidth[boundingRectsWidth.size()/2 -1];
		medianRectWidth = (medianRectWidth + 0.5 ) / 2;
	}
	else
	{
		medianRectWidth = boundingRectsWidth[boundingRectsWidth.size()/2] ;
	}

#endif


	// if the x position of two rects is too nearby..merge them .. a litte problem..
#if 1
	for (int i=0; i<(coarseBoundingRects.size() - 1); i++ )
	{
		int offsetX =  abs(coarseBoundingRects[i].x - coarseBoundingRects[i+1].x);

		if ( offsetX <  medianRectWidth/2 )
		{
			if ( coarseBoundingRects[i].x > coarseBoundingRects[i+1].x )
			{
				coarseBoundingRects[i].x = coarseBoundingRects[i+1].x;
			}

			if ( coarseBoundingRects[i].y > coarseBoundingRects[i+1].y )
			{
				coarseBoundingRects[i].y = coarseBoundingRects[i+1].y; 
			}
			
			if (  coarseBoundingRects[i].width <  coarseBoundingRects[i+1].width )
			{
				coarseBoundingRects[i].width =  coarseBoundingRects[i+1].width ;
			}

			if (  coarseBoundingRects[i].height <  coarseBoundingRects[i+1].height )
			{
				coarseBoundingRects[i].height =  coarseBoundingRects[i+1].height ;
			}
			
			coarseBoundingRects.erase(coarseBoundingRects.begin() + i+1);

			i--;	//删除了一个,当前位置还要再一次
		}
	}
#endif

	// if the width of rect is too large , separate them
#if 1
	for (int i=0; i<coarseBoundingRects.size(); i++ )
	{
		int widthMultiple = (int)(coarseBoundingRects[i].width / (double)medianRectWidth + 0.5 ) ;

		// if 
		if (widthMultiple >= 2)
		{
			Rect tmpRect;
			coarseBoundingRects.insert(coarseBoundingRects.begin() + i+1,(widthMultiple-1),tmpRect);
			int realWidth = coarseBoundingRects[i].width / widthMultiple;
			for (int j=0; j<widthMultiple; j++)
			{
				coarseBoundingRects[i+j].x = coarseBoundingRects[i].x + realWidth*j ;
				coarseBoundingRects[i+j].y = coarseBoundingRects[i].y;
				coarseBoundingRects[i+j].width = realWidth;
				coarseBoundingRects[i+j].height = coarseBoundingRects[i].height;

			}
		}

	}
#endif


	return 0;

}


#define _FixImageWidth 28
#define _FixImageHeight 28
//拷贝最大边长为28的图到 28*28图里
int copyCuttedImageToRegularImage(vector<Mat> &numImages,vector<Mat> &numImagesCutted)
{		
	for (int index=0; index< numImages.size(); index++)
	{
		// width < height in cutted image
		if ( (numImagesCutted[index].cols) <  (numImagesCutted[index].rows ) )
		{
			//留白
			int  left_offset =   ( _FixImageWidth - (numImagesCutted[index].cols) ) /2;

			for ( int i=0; i<(numImagesCutted[index].rows ); i++)
			{
				for (int j=0; j<(numImagesCutted[index].cols); j++ )
				{
					numImages[index].at<uchar>(i,j+left_offset) = numImagesCutted[index].at<uchar>(i,j);
				}
				
			}
		}

		// height < width in cutted image
		if ( (numImagesCutted[index].cols) >= (numImagesCutted[index].rows ) )
		{
			//留白
			int  up_offset =   ( _FixImageHeight - (numImagesCutted[index].rows) ) /2;

			for ( int i=0; i<(numImagesCutted[index].rows ); i++)
			{
				for (int j=0; j<(numImagesCutted[index].cols); j++ )
				{
					numImages[index].at<uchar>(i+up_offset,j) = numImagesCutted[index].at<uchar>(i,j);
				}

			}
		}

	}

	return 0;

}


//
int extractTheNumAndResize(Mat grayImage, vector<Mat> &numImages,const vector<Rect> &boundingRectsForContour )
{
	vector<Mat> numImagesCutted;
	numImagesCutted.resize(boundingRectsForContour.size());

	// 图像先切割出来
	for (int i=0; i<boundingRectsForContour.size(); i++)
	{
		 grayImage(boundingRectsForContour[i]).copyTo(numImagesCutted[i]);	
		 //imshow("cutte num image",numImagesCutted[i]);
		 //waitKey(500);
	}

	// resize the cutted image 
	for (int i=0; i<boundingRectsForContour.size(); i++)
	{
		int width;
		int height;
		// 宽度小于高度
		if ( numImagesCutted[i].cols <= numImagesCutted[i].rows)
		{
			height = _FixImageHeight;
			width = (int) (numImagesCutted[i].cols * height / numImagesCutted[i].rows );
			resize(numImagesCutted[i], numImagesCutted[i], Size(width,height), 0, 0,INTER_CUBIC);
		} 
		else	// 宽度大于高度
		{
			width = _FixImageWidth;
			int height = (int)(width * numImagesCutted[i].rows / numImagesCutted[i].cols);					 		
			cv::resize(numImagesCutted[i],numImagesCutted[i], Size(width,height), 0, 0,INTER_CUBIC);
		}	

		//imshow("resize cutte num image",numImagesCutted[i]);
		// waitKey(500);
	}

	//vector<Mat> numImagesTmp;
	 //numImagesTmp.resize(boundingRectsForContour.size());
	 Mat Mtmp(_FixImageHeight,_FixImageWidth, CV_8UC1, Scalar::all(255));	
	 //set white;
	for (int i=0; i<boundingRectsForContour.size(); i++)
	 {
		 numImages[i] = Mtmp.clone();
		 
	 }

	copyCuttedImageToRegularImage(numImages,numImagesCutted);

	for (int i=0; i<numImages.size(); i++)
	 {
		 //imshow("ok num image",numImages[i]);
		 //waitKey(500);
		 
	 }

	return 0;

}

//暂时就数字0_加到文件名前面
/// 查找最后一个 '\' 判断文件名 
int saveNumImgaeToFile(string pathStr)
{
	//string Str(“string”);
	return 0;
}


//切割图像并以灰度图保存
int cutOneImageAndSaveNum(CString PathCstr ,CString fileNameCstr)
{
	//CString 转 string
	//CString PathCstr = dlg.GetPathName();	
	CT2CA pszConvertedAnsiString (PathCstr);
	string PathStr(pszConvertedAnsiString);

	//CString fileNameCstr = dlg.GetFileName();
	CT2CA pszConvertedAnsiString2 (fileNameCstr);
	string fileNameStr(pszConvertedAnsiString2);

	//direct read as Gray Image
	Mat grayImage  = imread(PathStr,CV_LOAD_IMAGE_GRAYSCALE);
	imshow("test",grayImage);
	waitKey(30);

	//Change to canny Image 
#if 0
	Mat cannyImage;
	double threshold1 = 20;
	double threshold2 = 100;
	int aper_tureSize=5;
	bool L2gradient=true;
	Canny(grayImage, cannyImage, threshold1,threshold2, aper_tureSize,  L2gradient );	
	imshow("figureCanny",cannyImage);
#endif


	//Change to Binary Image  
#if 1
#pragma region Change to Binary Image  

	double thresh_otsu = 0.0;
	Mat binaryImage;
	//thresh_otsu = threshold(grayImage, binaryImage,  0, 255, CV_THRESH_BINARY|CV_THRESH_OTSU);
	thresh_otsu = threshold(grayImage, binaryImage,  220, 255, CV_THRESH_BINARY_INV);
	imshow("figure: Binary Image", binaryImage);

#pragma endregion Change to Binary Image  

#endif

	//vector< vector<Point> > filterContours ;
	vector<Rect> boundingRectsForContour;	// 已经是排序好后的，每个字符轮廓的外界矩形
	Mat binaryImageTmp = binaryImage.clone();
	separateNumsByContour( binaryImageTmp ,boundingRectsForContour);


	vector<Mat> numImages;
	numImages.resize( boundingRectsForContour.size());
	//extractTheNumAndResize(Mat grayImage, vector<Mat> &numImages,const vector<Rect> &boundingRectsForContour );
	//extractTheNumAndResize(grayImage, numImages,boundingRectsForContour );
	Mat binaryImageInv;
	threshold(grayImage, binaryImageInv,  220, 255, CV_THRESH_BINARY);
	extractTheNumAndResize(binaryImageInv, numImages,boundingRectsForContour );

	string fileNameOutput ;
	char t[256];
	string s;


	for (int i=0; i<numImages.size(); i++)
	{
		sprintf(t, "%d_", i);
		s = t;
		fileNameOutput =  s+fileNameStr;
		imwrite(fileNameOutput,numImages[i]);
	}

	return 0;
}

// Button:  切割图像并以灰度图保存
void COpencvMFCProjectTemplateDlg::OnBnClickedTest()
{
	BROWSEINFO   stBrowseInfo; 
	ITEMIDLIST *pstItemIdList;   
	TCHAR     acFilePath[_MAX_PATH]; 
	memset(&stBrowseInfo,   0,   sizeof(BROWSEINFO)); 
	stBrowseInfo.ulFlags   =   BIF_RETURNONLYFSDIRS;         // 只?返·μ回?目?录?         
	pstItemIdList   =   SHBrowseForFolder(&stBrowseInfo);     // open   select   directory   dialog 
	if (pstItemIdList != NULL )
	{
		SHGetPathFromIDList(pstItemIdList,   acFilePath);
	}
	else
	{
		return;
	}
	// build a string with wildcards(通í¨配?符·? *)
	CString strWildcard = CString(acFilePath);
	strWildcard += _T("\\*.bmp");
	// start working for files
	CString strFileName;
	CString strFilePath;
	CFileFind finder;
	BOOL bWorking = finder.FindFile(strWildcard);
	while (bWorking)
	{
		bWorking = finder.FindNextFile();
		// 好o?像?一ò?开a始ê?找ò到μ?的μ?是ê? . ..
		if (finder.IsDots()) 
		{
			continue;
		}
		if(!finder.IsDirectory()) 
		{ 
			strFilePath = finder.GetFilePath();    
			strFileName = finder.GetFileName();
			CString mergeFilePath( "mergeHogFeatures.txt");			 
			cutOneImageAndSaveNum(strFilePath,strFileName);
		}
	}//while (bWorking)
	finder.Close();
}

//old OnBnClickedTest()
#if 0 

//Test按钮：打开图像并显示
void COpencvMFCProjectTemplateDlg::OnBnClickedTest()
{
	// TODO: 在此添加控件通知处理程序代码

#pragma region 打开图像并显示

	// TODO: Add your control notification handler code here
	CFileDialog dlg(
		TRUE, _T("*.jpg"), NULL,
		OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY,
		_T("image files ( *.jpg ;*.bmp) |*.jpg;*.bmp| All Files (*.*) |*.*||"), 
		NULL
		);                                        // 选项图片的约定
	//dlg.m_ofn.lpstrTitle = _T("Open Image");    // 打开文件对话框的标题名
	if( dlg.DoModal() != IDOK )                    // 判断是否获得图片
		return;
	//CString 转 string
	CString PathCstr = dlg.GetPathName();	
	CT2CA pszConvertedAnsiString (PathCstr);
	string PathStr(pszConvertedAnsiString);

	CString fileNameCstr = dlg.GetFileName();
	CT2CA pszConvertedAnsiString2 (fileNameCstr);
	string fileNameStr(pszConvertedAnsiString2);

	//direct read as Gray Image
	Mat grayImage  = imread(PathStr,CV_LOAD_IMAGE_GRAYSCALE);
	imshow("test",grayImage);

#pragma endregion 打开图像并显示

	//Change to canny Image 
#if 0
	Mat cannyImage;
	double threshold1 = 20;
	double threshold2 = 100;
	int aper_tureSize=5;
	bool L2gradient=true;
	Canny(grayImage, cannyImage, threshold1,threshold2, aper_tureSize,  L2gradient );	
	imshow("figureCanny",cannyImage);
#endif


	//Change to Binary Image  
#if 1
#pragma region Change to Binary Image  

	double thresh_otsu = 0.0;
	Mat binaryImage;
	//thresh_otsu = threshold(grayImage, binaryImage,  0, 255, CV_THRESH_BINARY|CV_THRESH_OTSU);
	thresh_otsu = threshold(grayImage, binaryImage,  220, 255, CV_THRESH_BINARY_INV);
	imshow("figure: Binary Image", binaryImage);

#pragma endregion Change to Binary Image  

#endif

	//vector< vector<Point> > filterContours ;
	vector<Rect> boundingRectsForContour;	// 已经是排序好后的，每个字符轮廓的外界矩形
	separateNumsByContour( binaryImage ,boundingRectsForContour);


	vector<Mat> numImages;
	numImages.resize( boundingRectsForContour.size());
	//extractTheNumAndResize(Mat grayImage, vector<Mat> &numImages,const vector<Rect> &boundingRectsForContour );
	extractTheNumAndResize(grayImage, numImages,boundingRectsForContour );

	string fileNameOutput ;
	char t[256];
	string s;


	for (int i=0; i<numImages.size(); i++)
	{
		sprintf(t, "%d_", i);
		s = t;
		fileNameOutput =  s+fileNameStr;
		imwrite(fileNameOutput,numImages[i]);
	}

	//缩放图像到指定大小
#if 0   

	const int fixWidth = 600;
	Mat imageRead = imread(PathStr);
	Mat image;
	if(imageRead.cols != fixWidth)
	{
		int width = fixWidth;
		int height = (int)(width * imageRead.rows / imageRead.cols);		
		image.create(height, width, CV_8UC3);		
		cv::resize(imageRead, image, Size(width,height), 0, 0,INTER_CUBIC);
	}
	else
	{
		image = imageRead.clone();
	}

#endif





}

#endif
//only work for : 4 cells per block ...
Mat get_hogdescriptor_visu(Mat& origImg,  HOGDescriptor& hog, vector<float>& descriptorValues)
{   
	//Mat color_origImg;
	//cvtColor(origImg, color_origImg, CV_GRAY2RGB);

	float zoomFac = 6;
	Mat visu;
	resize(origImg, visu, Size(origImg.cols*zoomFac, origImg.rows*zoomFac));

	int blockSize       = hog.blockSize.width;
	int cellSize        = hog.cellSize.width;
	int gradientBinSize = hog.nbins;
	float radRangeForOneBin = M_PI/(float)gradientBinSize; // dividing 180° into 9 bins, how large (in rad) is one bin?

	// prepare data structure: 9 orientation / gradient strenghts for each cell
	int cells_in_x_dir = origImg.cols / cellSize;
	int cells_in_y_dir = origImg.rows/ cellSize;
	int totalnrofcells = cells_in_x_dir * cells_in_y_dir;
	float*** gradientStrengths = new float**[cells_in_y_dir];
	int** cellUpdateCounter   = new int*[cells_in_y_dir];
	for (int y=0; y<cells_in_y_dir; y++)
	{
		gradientStrengths[y] = new float*[cells_in_x_dir];
		cellUpdateCounter[y] = new int[cells_in_x_dir];
		for (int x=0; x<cells_in_x_dir; x++)
		{
			gradientStrengths[y][x] = new float[gradientBinSize];
			cellUpdateCounter[y][x] = 0;

			for (int bin=0; bin<gradientBinSize; bin++)
				gradientStrengths[y][x][bin] = 0.0;
		}
	}

	// nr of blocks = nr of cells - 1
	// since there is a new block on each cell (overlapping blocks!) but the last one
	//int blocks_in_x_dir = cells_in_x_dir - 1;	 
	//int blocks_in_y_dir = cells_in_y_dir - 1;
	//((winSize.width - blockSize.width)/blockStride.width + 1)
	//((winSize.height - blockSize.height)/blockStride.height + 1);  
	int blocks_in_x_dir =  (hog.winSize.width - hog.blockSize.width)/hog.blockStride.width + 1;
	int blocks_in_y_dir =  (hog.winSize.height - hog.blockSize.height)/hog.blockStride.height + 1;



	// compute gradient strengths per cell
	int descriptorDataIdx = 0;
	int cellx = 0;
	int celly = 0;

	for (int blockx=0; blockx<blocks_in_x_dir; blockx++)
	{
		for (int blocky=0; blocky<blocks_in_y_dir; blocky++)            
		{
			// 4 cells per block ...
			for (int cellNr=0; cellNr<4; cellNr++)
			{
				// compute corresponding cell nr
				int cellx = blockx;
				int celly = blocky;
				if (cellNr==1) celly++;
				if (cellNr==2) cellx++;
				if (cellNr==3)
				{
					cellx++;
					celly++;
				}		
				

				for (int bin=0; bin<gradientBinSize; bin++)
				{
					float gradientStrength = descriptorValues[ descriptorDataIdx ];
					descriptorDataIdx++;

					gradientStrengths[celly][cellx][bin] += gradientStrength;

				} // for (all bins)


				// note: overlapping blocks lead to multiple updates of this sum!
				// we therefore keep track how often a cell was updated,
				// to compute average gradient strengths
				cellUpdateCounter[celly][cellx]++;

			} // for (all cells)


		} // for (all block x pos)
	} // for (all block y pos)


	// compute average gradient strengths
	for (int celly=0; celly<cells_in_y_dir; celly++)
	{
		for (int cellx=0; cellx<cells_in_x_dir; cellx++)
		{

			float NrUpdatesForThisCell = (float)cellUpdateCounter[celly][cellx];

			// compute average gradient strenghts for each gradient bin direction
			for (int bin=0; bin<gradientBinSize; bin++)
			{
				gradientStrengths[celly][cellx][bin] /= NrUpdatesForThisCell;
			}
		}
	}


//	cout << "descriptorDataIdx = " << descriptorDataIdx << endl;

	// draw cells
	for (int celly=0; celly<cells_in_y_dir; celly++)
	{
		for (int cellx=0; cellx<cells_in_x_dir; cellx++)
		{
			int drawX = cellx * cellSize;
			int drawY = celly * cellSize;

			int mx = drawX + cellSize/2;
			int my = drawY + cellSize/2;

			rectangle(visu, Point(drawX*zoomFac,drawY*zoomFac), Point((drawX+cellSize)*zoomFac,(drawY+cellSize)*zoomFac), CV_RGB(100,100,100), 1);

			// draw in each cell all 9 gradient strengths
			for (int bin=0; bin<gradientBinSize; bin++)
			{
				float currentGradStrength = gradientStrengths[celly][cellx][bin];

				// no line to draw?
				if (currentGradStrength==0)
					continue;

				float currRad = bin * radRangeForOneBin + radRangeForOneBin/2;

				float dirVecX = cos( currRad );
				float dirVecY = sin( currRad );
				float maxVecLen = cellSize/2;
				float scale = 2.5; // just a visualization scale, to see the lines better

				// compute line coordinates
				float x1 = mx - dirVecX * currentGradStrength * maxVecLen * scale;
				float y1 = my - dirVecY * currentGradStrength * maxVecLen * scale;
				float x2 = mx + dirVecX * currentGradStrength * maxVecLen * scale;
				float y2 = my + dirVecY * currentGradStrength * maxVecLen * scale;

				// draw gradient visualization
				line(visu, Point(x1*zoomFac,y1*zoomFac), Point(x2*zoomFac,y2*zoomFac), CV_RGB(0,255,0), 1);

			} // for (all bins)

		} // for (cellx)
	} // for (celly)


	// don't forget to free memory allocated by helper data structures!
	for (int y=0; y<cells_in_y_dir; y++)
	{
		for (int x=0; x<cells_in_x_dir; x++)
		{
			delete[] gradientStrengths[y][x];            
		}
		delete[] gradientStrengths[y];
		delete[] cellUpdateCounter[y];
	}
	delete[] gradientStrengths;
	delete[] cellUpdateCounter;

	return visu;

} // get_hogdescriptor_visu


bool string_replace(std::string& str, const std::string& from, const std::string& to) 
{ 
	size_t start_pos = str.find(from); 
	if(start_pos == std::string::npos) 
		return false; 
	str.replace(start_pos, from.length(), to); 
	return true; 
} 

/// HoG feature 文本文件的名字和图像文件一样，后缀不一样
int saveHogFeatureToTxtFile(string imageFileName,int type, vector<float> &HoGfeatures)
{
	string feature_file = imageFileName;
	string_replace(feature_file, ".bmp",".txt");
	string_replace(feature_file, ".jpg",".txt");
	//string_replace(feature_file, ".txt", "-"+ to_string((_Longlong)(i)) +"-step1.txt");

	//std::cout << feature_file << endl;

	ofstream ofile(feature_file);
	if (ofile.is_open() && ofile.good())
	{
		ofile << type << " ";
		for (int j = 0; j < HoGfeatures.size(); j++)
		{

			ofile << j+ 1 << ":" << HoGfeatures[j] << " ";
		}
		ofile << endl;
	}
	ofile.close();

	return 0;
}

void get_filelist(char *foldname,vector<string>& flist )
{


	//vector<string> flist;
	HANDLE file;
	WIN32_FIND_DATA fileData;
	char line[1024];
	//wchar_t fn[1000];
	//char fn[1000];
	//mbstowcs(fn,(const char*)foldname,999);
	file = FindFirstFile(foldname, &fileData);
	FindNextFile(file, &fileData);
	while(FindNextFile(file, &fileData))
	{
		wcstombs(line,(const wchar_t*)fileData.cFileName,259);
		flist.push_back(line);
	}
	//return flist;
}
void COpencvMFCProjectTemplateDlg::OnBnClickedButtonHogtest()
{
	// TODO: 在此添加控件通知处理程序代码


	
#pragma region 打开图像并显示
		
	// TODO: Add your control notification handler code here
	CFileDialog dlg(
		TRUE, _T("*.jpg"), NULL,
		OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY,
		_T("image files ( *.jpg ;*.bmp) |*.jpg;*.bmp| All Files (*.*) |*.*||"), 
		NULL
		);                                        // 选项图片的约定
	//dlg.m_ofn.lpstrTitle = _T("Open Image");    // 打开文件对话框的标题名
	if( dlg.DoModal() != IDOK )                    // 判断是否获得图片
		return;
	//CString 转 string
	CString PathCstr = dlg.GetPathName();	
	CT2CA pszConvertedAnsiString (PathCstr);
	string PathStr(pszConvertedAnsiString);

	CString fileNameCstr = dlg.GetFileName();
	CT2CA pszConvertedAnsiString2 (fileNameCstr);
	string fileNameStr(pszConvertedAnsiString2);

	//direct read as Gray Image
	Mat grayImage  = imread(PathStr,CV_LOAD_IMAGE_GRAYSCALE);
	imshow("test",grayImage);

#pragma endregion 打开图像并显示

#pragma region HoG Parameters


	// for display Hog Features.
	//int defaultBlockSize = 21; 	 
	//int defaultCellSize = defaultBlockSize/2;  

	int defaultBlockSize = 21; 	 
	int defaultCellSize = defaultBlockSize/3;  //one block of 3*3 cell is best as paper said 
	int defaultBlockStride = defaultCellSize ;	
	int defaultBinSize = 9;
	int defaultImageSize = 28;
	//parameters of HOGDescriptor 
	Size winSize = Size(defaultImageSize,defaultImageSize);		// size of parking lot image is 128*96
	Size blockSize = Size(defaultBlockSize,defaultBlockSize);
	Size blockStride =Size(defaultBlockStride,defaultBlockStride);
	Size cellSize = Size(defaultCellSize,defaultCellSize);
	int nbins = defaultBinSize;
	Size winStride = Size(defaultImageSize,defaultImageSize);
	Size padding = Size(0,0);   // 会影响descriptors.size()的尺寸
	// construct hogDescriptor
	cv::HOGDescriptor hogDescriptor(winSize, blockSize, blockStride, cellSize, nbins);



#pragma endregion HoG Parameters

	vector<Point>locs;
	vector<float>  HoGfeatures;	
	hogDescriptor.compute(grayImage, HoGfeatures, winStride, padding, locs);	

	int type;
	const char *p = fileNameStr.c_str(); 
	type = p[0] - '0';

	saveHogFeatureToTxtFile(fileNameStr,type,HoGfeatures);

	//vector<string> fileList;
	//get_filelist(_T("C:\\Sunyard\\Project\\numRecognition\\Data"),fileList);

	//std::vector<float> ders;
	
	////only work for : 4 cells per block ...
	 //Mat DescriptorVirtual = get_hogdescriptor_visu(grayImage, hogDescriptor,HoGfeatures);
	 //imshow(" ",DescriptorVirtual);

}

int CalculateHoGAndSaveToTxt(CString strFilePath ,CString strFileName   )
{
	//CString 转 string
	//CString PathCstr = dlg.GetPathName();	
	CT2CA pszConvertedAnsiString (strFilePath);
	string PathStr(pszConvertedAnsiString);
	
	//direct read as Gray Image
	Mat grayImage  = imread(PathStr,CV_LOAD_IMAGE_GRAYSCALE);
	imshow("test",grayImage);

 

#pragma region HoG Parameters


	// for display Hog Features.
	//int defaultBlockSize = 21; 	 
	//int defaultCellSize = defaultBlockSize/2;  

	int defaultBlockSize = 21; 	 
	int defaultCellSize = defaultBlockSize/3;  //one block of 3*3 cell is best as paper said 
	int defaultBlockStride = defaultCellSize ;	
	int defaultBinSize = 9;
	int defaultImageSize = 28;
	//parameters of HOGDescriptor 
	Size winSize = Size(defaultImageSize,defaultImageSize);		// size of parking lot image is 128*96
	Size blockSize = Size(defaultBlockSize,defaultBlockSize);
	Size blockStride =Size(defaultBlockStride,defaultBlockStride);
	Size cellSize = Size(defaultCellSize,defaultCellSize);
	int nbins = defaultBinSize;
	Size winStride = Size(defaultImageSize,defaultImageSize);
	Size padding = Size(0,0);   // 会影响descriptors.size()的尺寸
	// construct hogDescriptor
	cv::HOGDescriptor hogDescriptor(winSize, blockSize, blockStride, cellSize, nbins);



#pragma endregion HoG Parameters

	vector<Point>locs;
	vector<float>  HoGfeatures;	
	hogDescriptor.compute(grayImage, HoGfeatures, winStride, padding, locs);	


	CT2CA pszConvertedAnsiString2 (strFileName);
	string fileNameStr(pszConvertedAnsiString2);

	int type;
	const char *p = fileNameStr.c_str(); 
	type = p[0] - '0';

	saveHogFeatureToTxtFile(fileNameStr,type,HoGfeatures);
	
	return 0;
}

void COpencvMFCProjectTemplateDlg::OnBnClickedButtonSavehogtotxt()
{
	// TODO: 在此添加控件通知处理程序代码

	BROWSEINFO   stBrowseInfo; 
	ITEMIDLIST *pstItemIdList;   
	TCHAR     acFilePath[_MAX_PATH]; 
	memset(&stBrowseInfo,   0,   sizeof(BROWSEINFO)); 
	stBrowseInfo.ulFlags   =   BIF_RETURNONLYFSDIRS;         // 只?返·μ回?目?录?         
	pstItemIdList   =   SHBrowseForFolder(&stBrowseInfo);     // open   select   directory   dialog 
	if (pstItemIdList != NULL )
	{
		SHGetPathFromIDList(pstItemIdList,   acFilePath);
	}
	else
	{
		return;
	}
	// build a string with wildcards(通í¨配?符·? *)
	CString strWildcard = CString(acFilePath);
	strWildcard += _T("\\*.bmp");
	// start working for files
	CString strFileName;
	CString strFilePath;
	CFileFind finder;
	BOOL bWorking = finder.FindFile(strWildcard);
	while (bWorking)
	{
		bWorking = finder.FindNextFile();
		// 好o?像?一ò?开a始ê?找ò到μ?的μ?是ê? . ..
		if (finder.IsDots()) 
		{
			continue;
		}
		if(!finder.IsDirectory()) 
		{ 
			strFilePath = finder.GetFilePath();    
			strFileName = finder.GetFileName();
			CalculateHoGAndSaveToTxt(strFilePath,strFileName);
		}
	}//while (bWorking)
	finder.Close();
}


void mergeHoGfeatures(CString mergeFilePath ,CString singleFilePath)
{
	//fstream  mergeFile; 
	//mergeFile.open("..\\mergeHogFeatures.txt",ios::app,0);
	 CT2CA pszConvertedAnsiString2 (mergeFilePath);
	 string mergeFilePathStr(pszConvertedAnsiString2);
	ofstream mergeFile(mergeFilePathStr,ios::app);

	if (mergeFile.is_open() && mergeFile.good())
	{
	 CT2CA pszConvertedAnsiString (singleFilePath);
	 string PathStr(pszConvertedAnsiString);
	 char buffer[100]={'\0'};  
	 //buffer[99] = '\0';
	 ifstream in(PathStr);  
	 if (! in.is_open())  
	 { cout << "Error opening file"; exit (1); }  

	 for (int i=0; i<100; i++)
	 {
		 buffer[i] = '\0';
	 }

	 while (!in.eof() )  
	 {  
		 in.read(buffer,99);
		 //in.getline (buffer,100);  
		 mergeFile << buffer ;  

		 for (int i=0; i<100; i++)
		 {
			 buffer[i] = '\0';
		 }
	 }  
	in.close();
	}
	mergeFile.close();

}


void COpencvMFCProjectTemplateDlg::OnBnClickedButtonMergehogfeatures()
{
	// TODO: 在此添加控件通知处理程序代码

	 
	BROWSEINFO   stBrowseInfo; 
	ITEMIDLIST *pstItemIdList;   
	TCHAR     acFilePath[_MAX_PATH]; 
	memset(&stBrowseInfo,   0,   sizeof(BROWSEINFO)); 
	stBrowseInfo.ulFlags   =   BIF_RETURNONLYFSDIRS;         // 只?返·μ回?目?录?         
	pstItemIdList   =   SHBrowseForFolder(&stBrowseInfo);     // open   select   directory   dialog 
	if (pstItemIdList != NULL )
	{
		SHGetPathFromIDList(pstItemIdList,   acFilePath);
	}
	else
	{
		return;
	}
	// build a string with wildcards(通í¨配?符·? *)
	CString strWildcard = CString(acFilePath);
	strWildcard += _T("\\*.txt");
	// start working for files
	CString strFileName;
	CString strFilePath;
	CFileFind finder;
	BOOL bWorking = finder.FindFile(strWildcard);
	while (bWorking)
	{
		bWorking = finder.FindNextFile();
		// 好o?像?一ò?开a始ê?找ò到μ?的μ?是ê? . ..
		if (finder.IsDots()) 
		{
			continue;
		}
		if(!finder.IsDirectory()) 
		{ 
			strFilePath = finder.GetFilePath();    
			strFileName = finder.GetFileName();
			CString mergeFilePath( "mergeHogFeatures.txt");
			mergeHoGfeatures(mergeFilePath ,strFilePath);
		}
	}//while (bWorking)
	finder.Close();
}

/// BinaryImage(0/255) the object is 255, background is 0
/// output: VerticalProjection
int CalculateVerticalProjection(Mat &BinaryImage,vector<int> &VerticalProjection)
{
	//clear the VerticalProjection
	for (int i=0; i<VerticalProjection.size(); i++)
	{
		VerticalProjection[i] = 0;
	}

	int ImageHeight = BinaryImage.rows;
	int ImageWidth = BinaryImage.cols;

	// first Height 
	for( int i = 0; i < ImageHeight ; ++i)
	{
		for( int j = 0; j < ImageWidth; ++j )
		{
			if ( BinaryImage.at<uchar>(i,j) > 254)
				//if ( SobelImage.at<uchar>(i,j) > 0)
			{
				//VerticalProjection.at<CV_32SC1>(i,1)++;
				//VerticalProjection.at<CV_8UC1>(i) = VerticalProjection.at<CV_8UC1>(i) + 1 ;		
				VerticalProjection[i]= VerticalProjection[i] + 1 ;		
			}
		}
	}

  /// blur the projection , avoid the noise 
	vector<int> VerticalProjectionBlur;
	VerticalProjectionBlur.resize(VerticalProjection.size());
	for (int i=0; i<VerticalProjection.size(); i++)
	{
		VerticalProjectionBlur[i] = 0;
	}
	int blurWindowSize = 7;
	double GuassianFilter[7] ={0.0702,0.1311,0.1907,0.2161,0.1907,0.1311,0.0702 };

	for( int i = blurWindowSize/2 ; i < (VerticalProjection.size() - blurWindowSize/2 -1) ; ++i)
	{
		
		//应该不会超过250,灰度变换区域..可能还是改成int更可靠吧
		VerticalProjectionBlur[i] = (int)(VerticalProjection[i-3] * GuassianFilter[0]
										  +VerticalProjection[i-2] * GuassianFilter[1]
										  +VerticalProjection[i-1] * GuassianFilter[2]
										  +VerticalProjection[i] * GuassianFilter[3]
										  +VerticalProjection[i+1] * GuassianFilter[4]
										  +VerticalProjection[i+2] * GuassianFilter[5]
										  +VerticalProjection[i+3] * GuassianFilter[6] 
										  +0.5);						
	}

	for (int i=0; i<VerticalProjection.size(); i++)
	{
		VerticalProjection[i] = VerticalProjectionBlur[i];
	}

	return 0;
}

/// BinaryImage(0/255) the object is 255, background is 0
/// output: HorizontalProjection
int CalculateHorizontalProjection(Mat &BinaryImage,vector<int> &HorizontalProjection)
{
	////clear the HorizontalProjection
	for (int i=0; i<HorizontalProjection.size(); i++)
	{
		HorizontalProjection[i] = 0;
	}

	int ImageHeight = BinaryImage.rows;
	int ImageWidth = BinaryImage.cols;

	// first Width 
	for( int j = 0; j < ImageWidth; ++j )
	{
		for( int i = 0; i < ImageHeight ; ++i)
		{
			if ( BinaryImage.at<uchar>(i,j) > 128)
			{					
				HorizontalProjection[j] = HorizontalProjection[j] + 1 ;		
			}
		}
	}


	/// blur the projection , avoid the noise 
#if 1


	/// blur the projection , avoid the noise 
	vector<int> HorizontalProjectionBlur;
	HorizontalProjectionBlur.resize(HorizontalProjection.size());
	for (int i=0; i<HorizontalProjectionBlur.size(); i++)
	{
		HorizontalProjectionBlur[i] = 0;
	}

	int blurWindowSize = 7;
	double GuassianFilter[7] ={0.0702,0.1311,0.1907,0.2161,0.1907,0.1311,0.0702 };

	for( int i = blurWindowSize/2 ; i < (HorizontalProjection.size() - blurWindowSize/2 -1) ; ++i)
	{

		//应该不会超过250,灰度变换区域..可能还是改成int更可靠吧
		HorizontalProjectionBlur[i] = (int)(HorizontalProjection[i-3] * GuassianFilter[0]
									+HorizontalProjection[i-2] * GuassianFilter[1]
									+HorizontalProjection[i-1] * GuassianFilter[2]
									+HorizontalProjection[i] * GuassianFilter[3]
									+HorizontalProjection[i+1] * GuassianFilter[4]
									+HorizontalProjection[i+2] * GuassianFilter[5]
									+HorizontalProjection[i+3] * GuassianFilter[6] 
									+0.5);						
	}

	for (int i=0; i<HorizontalProjection.size(); i++)
	{
		HorizontalProjection[i] = HorizontalProjectionBlur[i];
	}
#endif

	return 0;

}


// draw the Projection
 int ShowTheHistgramOfProjection(Mat& orgImage,vector<int> &HorizontalProjection)
 {
	 

	 // Draw the histograms for B, G and R
	 int hist_w = orgImage.cols; 
	 int hist_h = orgImage.rows;

	 /// Establish the number of bins
	 int histSize = 256;
	 int bin_w = cvRound( (double) hist_w/histSize );

	 Mat histImage( hist_h, hist_w, CV_8UC3, Scalar( 0,0,0) );

	 /// Normalize the result to [ 0, histImage.rows ]
	 normalize(HorizontalProjection, HorizontalProjection, 0, histImage.rows, NORM_MINMAX, -1, Mat() );

	 /// Draw for each channel
	 for( int i = 1; i < hist_w; i++ )
	 {
		 line( histImage, Point( bin_w*(i-1), hist_h - cvRound(HorizontalProjection[i-1]) ) ,
			 Point( bin_w*(i), hist_h - cvRound(HorizontalProjection[i]) ),
			 Scalar( 255, 0, 0), 2, 8, 0  );		 
	 }

	 imshow("ShowTheHistgramOfProjection",histImage);

	 return 0;
 }


void COpencvMFCProjectTemplateDlg::OnBnClickedButtonReadimageandnumrecognition()
{
	// TODO: 在此添加控件通知处理程序代码


#pragma region 打开图像并显示

	// TODO: Add your control notification handler code here
	CFileDialog dlg(
		TRUE, _T("*.jpg"), NULL,
		OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY,
		_T("image files ( *.jpg ;*.bmp) |*.jpg;*.bmp| All Files (*.*) |*.*||"), 
		NULL
		);                                        // 选项图片的约定
	//dlg.m_ofn.lpstrTitle = _T("Open Image");    // 打开文件对话框的标题名
	if( dlg.DoModal() != IDOK )                    // 判断是否获得图片
		return;
	//CString 转 string
	CString PathCstr = dlg.GetPathName();	
	CT2CA pszConvertedAnsiString (PathCstr);
	string PathStr(pszConvertedAnsiString);

	CString fileNameCstr = dlg.GetFileName();
	CT2CA pszConvertedAnsiString2 (fileNameCstr);
	string fileNameStr(pszConvertedAnsiString2);

	//direct read as Gray Image
	Mat grayImage  = imread(PathStr,CV_LOAD_IMAGE_GRAYSCALE);
	imshow("test",grayImage);

#pragma endregion 打开图像并显示

	

	//Change to Binary Image  
#if 1
#pragma region Change to Binary Image  

	double thresh_otsu = 0.0;
	Mat binaryImage;

	//thresh_otsu = threshold(grayImage, binaryImage,  0, 255, CV_THRESH_BINARY|CV_THRESH_OTSU);
	thresh_otsu = threshold(grayImage, binaryImage,  0, 255, CV_THRESH_BINARY_INV|CV_THRESH_OTSU);
	//thresh_otsu = threshold(grayImage, binaryImage,  220, 255, CV_THRESH_BINARY_INV);
	imshow("figure: Binary Image", binaryImage);

#pragma endregion Change to Binary Image  

#endif

	///Calculate HorizontalProjection
#if 0

	vector<int> HorizontalProjection;
	HorizontalProjection.resize(binaryImage.cols);

	CalculateHorizontalProjection(binaryImage,HorizontalProjection);

	ShowTheHistgramOfProjection(binaryImage,HorizontalProjection);

#endif


	//vector< vector<Point> > filterContours ;
	vector<Rect> boundingRectsForContour;	// 已经是排序好后的，每个字符轮廓的外界矩形
	Mat binaryImageTmp = binaryImage.clone();
		
	//int erodeSize = 2;
	//int dilateSize = 2;
	//Mat elementForErode = getStructuringElement(MORPH_RECT, Size(erodeSize, erodeSize), Point(-1, -1) );  
	//Mat elementForDilate = getStructuringElement(MORPH_RECT, Size(dilateSize, dilateSize), Point(-1, -1) ); 
	//erode(binaryImageTmp ,binaryImageTmp , elementForErode );
	//dilate(binaryImageTmp ,binaryImageTmp , elementForDilate);

	separateNumsByContour( binaryImageTmp ,boundingRectsForContour);

	
    //vector<Rect> boundingRectsForContour;
	fineSeparateByContourAnalyse(boundingRectsForContour,boundingRectsForContour);


	/// imshow the fine separate nums...
#if 0

	for (int i=0; i<boundingRectsForContour.size(); i++)
	{
		//boundingRectsForContour[i] = boundingRect(filterContours[i]);
		//boundingRectsXPosition[i] =  boundingRectsForContour[i].x;
		rectangle(grayImage,boundingRectsForContour[i],Scalar(0, 0, 0));

	}
	imshow("fine coutour filled with BoundingRect",grayImage);

#endif


	vector<Mat> numImages;
	numImages.resize( boundingRectsForContour.size());
	//extractTheNumAndResize(Mat grayImage, vector<Mat> &numImages,const vector<Rect> &boundingRectsForContour );
	//extractTheNumAndResize(grayImage, numImages,boundingRectsForContour );
	Mat binaryImageInv;
	//double thresh_otsu = 0.0;
	thresh_otsu = threshold(grayImage, binaryImageInv,  0, 255, CV_THRESH_BINARY|CV_THRESH_OTSU);
	//thresh_otsu = threshold(grayImage, binaryImage,  0, 255, CV_THRESH_BINARY_INV|CV_THRESH_OTSU);
	extractTheNumAndResize(binaryImageInv, numImages,boundingRectsForContour );


	//HoG detection
#if 1



#pragma region HoG Parameters
	
	// for display Hog Features.
	//int defaultBlockSize = 21; 	 
	//int defaultCellSize = defaultBlockSize/2;  

	int defaultBlockSize = 21; 	 
	int defaultCellSize = defaultBlockSize/3;  //one block of 3*3 cell is best as paper said 
	int defaultBlockStride = defaultCellSize ;	
	int defaultBinSize = 9;
	int defaultImageSize = 28;
	//parameters of HOGDescriptor 
	Size winSize = Size(defaultImageSize,defaultImageSize);		// size of parking lot image is 128*96
	Size blockSize = Size(defaultBlockSize,defaultBlockSize);
	Size blockStride =Size(defaultBlockStride,defaultBlockStride);
	Size cellSize = Size(defaultCellSize,defaultCellSize);
	int nbins = defaultBinSize;
	Size winStride = Size(defaultImageSize,defaultImageSize);
	Size padding = Size(0,0);   // 会影响descriptors.size()的尺寸
	// construct hogDescriptor
	cv::HOGDescriptor hogDescriptor(winSize, blockSize, blockStride, cellSize, nbins);



#pragma endregion HoG Parameters

	vector<Point>locs;
	vector<float>  HoGfeatures;	
	hogDescriptor.compute(grayImage, HoGfeatures, winStride, padding, locs);	


#endif

	string svmModelFile = "mergeHogFeatures_RegularBinaryHoG.txt.model";
	struct svm_model* svmModels = svm_load_model(svmModelFile.c_str());

	int HoGfeaturesVecLength = 324;
	svm_node* _x = (struct svm_node *) malloc( (HoGfeaturesVecLength+1)*sizeof(struct svm_node) );
	double prob_estimates[10] = {0.0};
	vector<int> numRecognitionResult;
	numRecognitionResult.resize(numImages.size());
	for (int i=0; i<numImages.size(); i++)
	{
		hogDescriptor.compute(numImages[i], HoGfeatures, winStride, padding, locs);
		
		ConvertToLibSVMFormat(HoGfeatures, HoGfeatures.size(), _x);
		numRecognitionResult[i] = (int)svm_predict_probability(svmModels , _x, prob_estimates);
			 
	}


	free(_x);	
	svm_free_and_destroy_model(&svmModels);

 /*
	for (int k = 0; k < this->lotCount; k++)
	{
		ConvertToLibSVMFormat(this->HoGfeatures[k], this->HoGfeatures[k].size(), _x);
		this->lotStatus[k] = (ParkingLotResult)(int)svm_predict_probability(ParkingLotHoG::svmModels[k], _x, prob_estimates);

		
		this->lotStatusProbEstimate[k][svmModels[k]->label[0]] = prob_estimates[0]; 
		this->lotStatusProbEstimate[k][svmModels[k]->label[1]] = prob_estimates[1]; 
		this->lotStatusProbEstimate[k][svmModels[k]->label[2]] = prob_estimates[2]; 

#ifdef DEBUG_ParkingLot
		printf(" %d parkingLot prob_estimates: [%d %f]  [%d %f]  [%d %f] \n",k+1, 
			svmModels[k]->label[0],prob_estimates[0], 
			svmModels[k]->label[1],prob_estimates[1],
			svmModels[k]->label[2],prob_estimates[2]);
#endif 
	}*/

	

	//vector<Mat> numImages;
	//numImages.resize( boundingRectsForContour.size());
	////extractTheNumAndResize(Mat grayImage, vector<Mat> &numImages,const vector<Rect> &boundingRectsForContour );
	////extractTheNumAndResize(grayImage, numImages,boundingRectsForContour );
	//Mat binaryImageInv;
	//threshold(grayImage, binaryImageInv,  220, 255, CV_THRESH_BINARY);
	//extractTheNumAndResize(binaryImageInv, numImages,boundingRectsForContour );
}


int dealWithCutteNum(CString strFilePath,CString strFileName)
{
	//CString 转 string
	//CString PathCstr = dlg.GetPathName();	
	CT2CA pszConvertedAnsiString (strFilePath);
	string PathStr(pszConvertedAnsiString);

	//CString fileNameCstr = dlg.GetFileName();
	CT2CA pszConvertedAnsiString2 (strFileName);
	string fileNameStr(pszConvertedAnsiString2);

	//direct read as Gray Image
	Mat grayImage  = imread(PathStr,CV_LOAD_IMAGE_GRAYSCALE);
	//imshow("test",grayImage);


	//Change to Binary Image  
#if 1
#pragma region Change to Binary Image  

	double thresh_otsu = 0.0;
	Mat binaryImage;

	//thresh_otsu = threshold(grayImage, binaryImage,  0, 255, CV_THRESH_BINARY|CV_THRESH_OTSU);
	thresh_otsu = threshold(grayImage, binaryImage,  0, 255, CV_THRESH_BINARY_INV|CV_THRESH_OTSU);
	//thresh_otsu = threshold(grayImage, binaryImage,  220, 255, CV_THRESH_BINARY_INV);
	imshow("figure: Binary Image", binaryImage);

#pragma endregion Change to Binary Image  

#endif



	// resize the cutted image 
	
		int width;
		int height;
		// 宽度小于高度
		if ( binaryImage.cols <= binaryImage.rows)
		{
			height = _FixImageHeight;
			width = (int) (binaryImage.cols * height / binaryImage.rows );
			resize(binaryImage, binaryImage, Size(width,height), 0, 0,INTER_CUBIC);
		} 
		else	// 宽度大于高度
		{
			width = _FixImageWidth;
			int height = (int)(width * binaryImage.rows / binaryImage.cols);					 		
			cv::resize(binaryImage,binaryImage, Size(width,height), 0, 0,INTER_CUBIC);
		}	

		//imshow("resize cutte num image",numImagesCutted[i]);
		// waitKey(500);


	//vector<Mat> numImagesTmp;
	//numImagesTmp.resize(boundingRectsForContour.size());
	Mat Mtmp(_FixImageHeight,_FixImageWidth, CV_8UC1, Scalar::all(255));	

	// for call the function copyCuttedImageToRegularImage
	vector<Mat> numImages(1);
	vector<Mat> numImagesCutted(1);
	//numImages.re
	numImages[0] = Mtmp.clone();
	numImagesCutted[0] = binaryImage.clone();
	 

	copyCuttedImageToRegularImage(numImages,numImagesCutted);

	string fileNameOutput ;
	char t[256];
	string s;
	int i=0;	
	sprintf(t, "%d_", i);
	s = t;
	fileNameOutput =  s+fileNameStr;
	imwrite(fileNameOutput,numImages[0]);
	return 0;
}

void COpencvMFCProjectTemplateDlg::OnBnClickedButtonDealwithcuttednum()
{
	BROWSEINFO   stBrowseInfo; 
	ITEMIDLIST *pstItemIdList;   
	TCHAR     acFilePath[_MAX_PATH]; 
	memset(&stBrowseInfo,   0,   sizeof(BROWSEINFO)); 
	stBrowseInfo.ulFlags   =   BIF_RETURNONLYFSDIRS;         // 只?返·μ回?目?录?         
	pstItemIdList   =   SHBrowseForFolder(&stBrowseInfo);     // open   select   directory   dialog 
	if (pstItemIdList != NULL )
	{
		SHGetPathFromIDList(pstItemIdList,   acFilePath);
	}
	else
	{
		return;
	}
	// build a string with wildcards(通í¨配?符·? *)
	CString strWildcard = CString(acFilePath);
	strWildcard += _T("\\*.bmp");
	// start working for files
	CString strFileName;
	CString strFilePath;
	CFileFind finder;
	BOOL bWorking = finder.FindFile(strWildcard);
	while (bWorking)
	{
		bWorking = finder.FindNextFile();
		// 好o?像?一ò?开a始ê?找ò到μ?的μ?是ê? . ..
		if (finder.IsDots()) 
		{
			continue;
		}
		if(!finder.IsDirectory()) 
		{ 
			strFilePath = finder.GetFilePath();    
			strFileName = finder.GetFileName();
			dealWithCutteNum(strFilePath,strFileName);
		}
	}//while (bWorking)
	finder.Close();
}
 

int separateSingleNumsByContour(Mat &binaryImage ,vector<Rect>&boundingRectsForContour)
{


#pragma region detect Contour
	vector< vector<Point> > filterContours;
	vector< vector<Point> > contours;   // 轮廓     
	vector< vector<Point> > theLargestFilterContours;
	//vector< vector<Point> > filterContours; // 筛选后的轮廓  
	vector< Vec4i > hierarchy;    // 轮廓的结构信息   
	contours.clear();    
	hierarchy.clear();   
	filterContours.clear();  

	findContours(binaryImage, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);    

	// 去除伪轮廓: 轮廓上像素点数太少的 
	for (size_t i = 0; i < contours.size(); i++)   
	{  
		if (fabs(contourArea(Mat(contours[i]))) > 20)
			filterContours.push_back(contours[i]);  
	}  

	if (filterContours.size() ==0)
	{
		return -1;
	}

	//binaryImage.setTo(0);  
	//drawContours(binaryImage, filterContours, -1, Scalar(255,255,255), -1); //8, hierarchy); 
	//imshow("coutour filled",binaryImage);

#pragma endregion detect Contour

	//double area0 = contourArea(contour);
	vector<int> contourAreas;
	contourAreas.resize(filterContours.size());
	
	// if find larger than two contour. keep the largest contour 
	if (filterContours.size()>=2)
	{

		for (size_t i = 0; i < filterContours.size(); i++)
		{
			contourAreas[i] = (int)(contourArea(filterContours[i]));
		}
		//find the largest contour 
		sort(contourAreas.begin(),contourAreas.end());
				
		for (size_t i = 0; i < filterContours.size(); i++)
		{
			if (    contourAreas[contourAreas.size()-1] 
			     ==   (int)(contourArea(filterContours[i])) )
			{
				theLargestFilterContours.push_back(filterContours[i]); 
			}
		}
	}
	else	//only one contour
	{
		theLargestFilterContours.push_back(filterContours[0]); 
	}

	

	boundingRectsForContour.resize(theLargestFilterContours.size());
	boundingRectsForContour[0] = boundingRect(theLargestFilterContours[0]);
		
	return 0;
}
int DealWithMNIST(CString strFilePath,CString strFileName)
{
	//CString 转 string
	//CString PathCstr = dlg.GetPathName();	
	CT2CA pszConvertedAnsiString (strFilePath);
	string PathStr(pszConvertedAnsiString);

	//CString fileNameCstr = dlg.GetFileName();
	CT2CA pszConvertedAnsiString2 (strFileName);
	string fileNameStr(pszConvertedAnsiString2);

	//direct read as Gray Image
	Mat grayImage  = imread(PathStr,CV_LOAD_IMAGE_GRAYSCALE);
	//imshow("test",grayImage);


	//Change to Binary Image  

#pragma region Change to Binary Image  

	double thresh_otsu = 0.0;
	Mat binaryImage;

	//thresh_otsu = threshold(grayImage, binaryImage,  0, 255, CV_THRESH_BINARY|CV_THRESH_OTSU);
	thresh_otsu = threshold(grayImage, binaryImage,  0, 255, CV_THRESH_BINARY_INV|CV_THRESH_OTSU);
	//thresh_otsu = threshold(grayImage, binaryImage,  220, 255, CV_THRESH_BINARY_INV);
	imshow("figure: Binary Image", binaryImage);

#pragma endregion Change to Binary Image  


	vector<Rect> boundingRectsForContour;	// 已经是排序好后的，每个字符轮廓的外界矩形
	Mat binaryImageTmp = binaryImage.clone();
	int findNum = separateSingleNumsByContour( binaryImageTmp ,boundingRectsForContour);

	if (findNum == -1)
	{
		return -1;
	}

	vector<Mat> numImages;
	numImages.resize( boundingRectsForContour.size());
	//extractTheNumAndResize(Mat grayImage, vector<Mat> &numImages,const vector<Rect> &boundingRectsForContour );
	//extractTheNumAndResize(grayImage, numImages,boundingRectsForContour );
	Mat binaryImageInv;
	threshold(grayImage, binaryImageInv,  220, 255, CV_THRESH_BINARY);
	extractTheNumAndResize(binaryImageInv, numImages,boundingRectsForContour );

	string fileNameOutput ;
	char t[256];
	string s;


	for (int i=0; i<numImages.size(); i++)
	{
		//sprintf(t, "%d_", i);
		//s = t;
		//fileNameOutput =  s+fileNameStr;
		imwrite(fileNameStr,numImages[i]);
	}

	return 0;

}

// 上下都留白的MNIST的改成自适应28*28(最长的边是占满28的)
void COpencvMFCProjectTemplateDlg::OnBnClickedButtonDealwithmnist()
{
	// TODO: 在此添加控件通知处理程序代码


	BROWSEINFO   stBrowseInfo; 
	ITEMIDLIST *pstItemIdList;   
	TCHAR     acFilePath[_MAX_PATH]; 
	memset(&stBrowseInfo,   0,   sizeof(BROWSEINFO)); 
	stBrowseInfo.ulFlags   =   BIF_RETURNONLYFSDIRS;         // 只?返·μ回?目?录?         
	pstItemIdList   =   SHBrowseForFolder(&stBrowseInfo);     // open   select   directory   dialog 
	if (pstItemIdList != NULL )
	{
		SHGetPathFromIDList(pstItemIdList,   acFilePath);
	}
	else
	{
		return;
	}
	// build a string with wildcards(通í¨配?符·? *)
	CString strWildcard = CString(acFilePath);
	strWildcard += _T("\\*.bmp");
	// start working for files
	CString strFileName;
	CString strFilePath;
	CFileFind finder;
	BOOL bWorking = finder.FindFile(strWildcard);
	while (bWorking)
	{
		bWorking = finder.FindNextFile();
		// 好o?像?一ò?开a始ê?找ò到μ?的μ?是ê? . ..
		if (finder.IsDots()) 
		{
			continue;
		}
		if(!finder.IsDirectory()) 
		{ 
			strFilePath = finder.GetFilePath();    
			strFileName = finder.GetFileName();
			DealWithMNIST(strFilePath,strFileName);
		}
	}//while (bWorking)
	finder.Close();



}

//银行卡号识别...
void COpencvMFCProjectTemplateDlg::OnBnClickedButtonBankcardnumrecognition()
{
	// TODO: 在此添加控件通知处理程序代码
	
	// TODO: 在此添加控件通知处理程序代码


#pragma region 打开图像并显示

	// TODO: Add your control notification handler code here
	CFileDialog dlg(
		TRUE, _T("*.jpg"), NULL,
		OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY,
		_T("image files ( *.jpg ;*.bmp) |*.jpg;*.bmp| All Files (*.*) |*.*||"), 
		NULL
		);                                        // 选项图片的约定
	//dlg.m_ofn.lpstrTitle = _T("Open Image");    // 打开文件对话框的标题名
	if( dlg.DoModal() != IDOK )                    // 判断是否获得图片
		return;
	//CString 转 string
	CString PathCstr = dlg.GetPathName();	
	CT2CA pszConvertedAnsiString (PathCstr);
	string PathStr(pszConvertedAnsiString);

	CString fileNameCstr = dlg.GetFileName();
	CT2CA pszConvertedAnsiString2 (fileNameCstr);
	string fileNameStr(pszConvertedAnsiString2);

	//direct read as Gray Image
	Mat grayImage  = imread(PathStr,CV_LOAD_IMAGE_GRAYSCALE);
	imshow("test",grayImage);

#pragma endregion 打开图像并显示

	

	//Change to Binary Image  
#if 1
 
	double thresh_otsu = 0.0;
	Mat binaryImage;

	//thresh_otsu = threshold(grayImage, binaryImage,  0, 255, CV_THRESH_BINARY|CV_THRESH_OTSU);
	thresh_otsu = threshold(grayImage, binaryImage,  0, 255, CV_THRESH_BINARY_INV|CV_THRESH_OTSU);
	//thresh_otsu = threshold(grayImage, binaryImage,  220, 255, CV_THRESH_BINARY_INV);
	//imshow("figure: Binary Image", binaryImage); 

#endif



	//Change to canny Image 
#if 1
	Mat cannyImage;
	double threshold1 = 500;
	double threshold2 = 600;
	int aper_tureSize=5;
	bool L2gradient=true;
	Canny(grayImage, cannyImage, threshold1,threshold2, aper_tureSize,  L2gradient );	
	imshow("figureCanny",cannyImage);
#endif

	Mat SobelImage;

	//Soble 
#if 1
	int xorder = 1;
	int yorder = 0;
	int ksize = 5;	
	//Sobel(grayImage,SobelImage, -1, xorder, yorder, ksize=3);
	Sobel(grayImage,SobelImage, CV_16S, xorder, yorder, ksize);
	
	imshow("figure: Sobel Image", SobelImage);  

	return ;

//	double thresh_otsu = 0.0;
	thresh_otsu = threshold(SobelImage, SobelImage, 0, 255, CV_THRESH_BINARY|CV_THRESH_OTSU);

	// if otsu Threshold is too small.use 30
	if (thresh_otsu <30)
		threshold(SobelImage, SobelImage, 30, 255, CV_THRESH_BINARY);

	imshow("figure: Sobel Binary Image", SobelImage);  

#endif
	
	//vector< vector<Point> > filterContours ;
	vector<Rect> boundingRectsForContour;	// 已经是排序好后的，每个字符轮廓的外界矩形
	Mat binaryImageTmp = cannyImage.clone();
		
	//int erodeSize = 2;
	//int dilateSize = 2;
	//Mat elementForErode = getStructuringElement(MORPH_RECT, Size(erodeSize, erodeSize), Point(-1, -1) );  
	//Mat elementForDilate = getStructuringElement(MORPH_RECT, Size(dilateSize, dilateSize), Point(-1, -1) ); 
	//erode(binaryImageTmp ,binaryImageTmp , elementForErode );
	//dilate(binaryImageTmp ,binaryImageTmp , elementForDilate);

	separateNumsByContour( binaryImageTmp ,boundingRectsForContour);

	
    //vector<Rect> boundingRectsForContour;
	fineSeparateByContourAnalyse(boundingRectsForContour,boundingRectsForContour);


	/// imshow the fine separate nums...
#if 0

	for (int i=0; i<boundingRectsForContour.size(); i++)
	{
		//boundingRectsForContour[i] = boundingRect(filterContours[i]);
		//boundingRectsXPosition[i] =  boundingRectsForContour[i].x;
		rectangle(grayImage,boundingRectsForContour[i],Scalar(0, 0, 0));

	}
	imshow("fine coutour filled with BoundingRect",grayImage);

#endif


	vector<Mat> numImages;
	numImages.resize( boundingRectsForContour.size());
	//extractTheNumAndResize(Mat grayImage, vector<Mat> &numImages,const vector<Rect> &boundingRectsForContour );
	//extractTheNumAndResize(grayImage, numImages,boundingRectsForContour );
	Mat binaryImageInv;
	//double thresh_otsu = 0.0;
	thresh_otsu = threshold(grayImage, binaryImageInv,  0, 255, CV_THRESH_BINARY|CV_THRESH_OTSU);
	//thresh_otsu = threshold(grayImage, binaryImage,  0, 255, CV_THRESH_BINARY_INV|CV_THRESH_OTSU);
	extractTheNumAndResize(binaryImageInv, numImages,boundingRectsForContour );


	//HoG detection
#if 1



#pragma region HoG Parameters
	
	// for display Hog Features.
	//int defaultBlockSize = 21; 	 
	//int defaultCellSize = defaultBlockSize/2;  

	int defaultBlockSize = 21; 	 
	int defaultCellSize = defaultBlockSize/3;  //one block of 3*3 cell is best as paper said 
	int defaultBlockStride = defaultCellSize ;	
	int defaultBinSize = 9;
	int defaultImageSize = 28;
	//parameters of HOGDescriptor 
	Size winSize = Size(defaultImageSize,defaultImageSize);		// size of parking lot image is 128*96
	Size blockSize = Size(defaultBlockSize,defaultBlockSize);
	Size blockStride =Size(defaultBlockStride,defaultBlockStride);
	Size cellSize = Size(defaultCellSize,defaultCellSize);
	int nbins = defaultBinSize;
	Size winStride = Size(defaultImageSize,defaultImageSize);
	Size padding = Size(0,0);   // 会影响descriptors.size()的尺寸
	// construct hogDescriptor
	cv::HOGDescriptor hogDescriptor(winSize, blockSize, blockStride, cellSize, nbins);



#pragma endregion HoG Parameters

	vector<Point>locs;
	vector<float>  HoGfeatures;	
	hogDescriptor.compute(grayImage, HoGfeatures, winStride, padding, locs);	


#endif

	string svmModelFile = "mergeHogFeatures_RegularBinaryHoG.txt.model";
	struct svm_model* svmModels = svm_load_model(svmModelFile.c_str());

	int HoGfeaturesVecLength = 324;
	svm_node* _x = (struct svm_node *) malloc( (HoGfeaturesVecLength+1)*sizeof(struct svm_node) );
	double prob_estimates[10] = {0.0};
	vector<int> numRecognitionResult;
	numRecognitionResult.resize(numImages.size());
	for (int i=0; i<numImages.size(); i++)
	{
		hogDescriptor.compute(numImages[i], HoGfeatures, winStride, padding, locs);
		
		ConvertToLibSVMFormat(HoGfeatures, HoGfeatures.size(), _x);
		numRecognitionResult[i] = (int)svm_predict_probability(svmModels , _x, prob_estimates);
			 
	}


	free(_x);	
	svm_free_and_destroy_model(&svmModels);

	
	CString theString;
	CString tmpString;
	for (int i=0; i<numRecognitionResult.size(); i++)
	{
		 tmpString.Format("_%d",numRecognitionResult[i]);
		theString = theString + tmpString;
	}
	//LPTSTR lpsz =(LPTSTR)(LPCTSTR)theString;
	MessageBox(theString);

 /*
	for (int k = 0; k < this->lotCount; k++)
	{
		ConvertToLibSVMFormat(this->HoGfeatures[k], this->HoGfeatures[k].size(), _x);
		this->lotStatus[k] = (ParkingLotResult)(int)svm_predict_probability(ParkingLotHoG::svmModels[k], _x, prob_estimates);

		
		this->lotStatusProbEstimate[k][svmModels[k]->label[0]] = prob_estimates[0]; 
		this->lotStatusProbEstimate[k][svmModels[k]->label[1]] = prob_estimates[1]; 
		this->lotStatusProbEstimate[k][svmModels[k]->label[2]] = prob_estimates[2]; 

#ifdef DEBUG_ParkingLot
		printf(" %d parkingLot prob_estimates: [%d %f]  [%d %f]  [%d %f] \n",k+1, 
			svmModels[k]->label[0],prob_estimates[0], 
			svmModels[k]->label[1],prob_estimates[1],
			svmModels[k]->label[2],prob_estimates[2]);
#endif 
	}*/

	

	//vector<Mat> numImages;
	//numImages.resize( boundingRectsForContour.size());
	////extractTheNumAndResize(Mat grayImage, vector<Mat> &numImages,const vector<Rect> &boundingRectsForContour );
	////extractTheNumAndResize(grayImage, numImages,boundingRectsForContour );
	//Mat binaryImageInv;
	//threshold(grayImage, binaryImageInv,  220, 255, CV_THRESH_BINARY);
	//extractTheNumAndResize(binaryImageInv, numImages,boundingRectsForContour );
}


//用阈值分割的效果貌似不咋地呀...
//直接提轮廓吧 
#if 0

void COpencvMFCProjectTemplateDlg::OnBnClickedButtonBankcardnumrecognition()
{
	// TODO: 在此添加控件通知处理程序代码
	
	// TODO: 在此添加控件通知处理程序代码


#pragma region 打开图像并显示

	// TODO: Add your control notification handler code here
	CFileDialog dlg(
		TRUE, _T("*.jpg"), NULL,
		OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY,
		_T("image files ( *.jpg ;*.bmp) |*.jpg;*.bmp| All Files (*.*) |*.*||"), 
		NULL
		);                                        // 选项图片的约定
	//dlg.m_ofn.lpstrTitle = _T("Open Image");    // 打开文件对话框的标题名
	if( dlg.DoModal() != IDOK )                    // 判断是否获得图片
		return;
	//CString 转 string
	CString PathCstr = dlg.GetPathName();	
	CT2CA pszConvertedAnsiString (PathCstr);
	string PathStr(pszConvertedAnsiString);

	CString fileNameCstr = dlg.GetFileName();
	CT2CA pszConvertedAnsiString2 (fileNameCstr);
	string fileNameStr(pszConvertedAnsiString2);

	//direct read as Gray Image
	Mat grayImage  = imread(PathStr,CV_LOAD_IMAGE_GRAYSCALE);
	imshow("test",grayImage);

#pragma endregion 打开图像并显示

	

	//Change to Binary Image  
#if 1
#pragma region Change to Binary Image  

	double thresh_otsu = 0.0;
	Mat binaryImage;

	//thresh_otsu = threshold(grayImage, binaryImage,  0, 255, CV_THRESH_BINARY|CV_THRESH_OTSU);
	thresh_otsu = threshold(grayImage, binaryImage,  0, 255, CV_THRESH_BINARY_INV|CV_THRESH_OTSU);
	//thresh_otsu = threshold(grayImage, binaryImage,  220, 255, CV_THRESH_BINARY_INV);
	imshow("figure: Binary Image", binaryImage);

#pragma endregion Change to Binary Image  

#endif

	///Calculate HorizontalProjection
#if 0

	vector<int> HorizontalProjection;
	HorizontalProjection.resize(binaryImage.cols);

	CalculateHorizontalProjection(binaryImage,HorizontalProjection);

	ShowTheHistgramOfProjection(binaryImage,HorizontalProjection);

#endif


	//vector< vector<Point> > filterContours ;
	vector<Rect> boundingRectsForContour;	// 已经是排序好后的，每个字符轮廓的外界矩形
	Mat binaryImageTmp = binaryImage.clone();
		
	//int erodeSize = 2;
	//int dilateSize = 2;
	//Mat elementForErode = getStructuringElement(MORPH_RECT, Size(erodeSize, erodeSize), Point(-1, -1) );  
	//Mat elementForDilate = getStructuringElement(MORPH_RECT, Size(dilateSize, dilateSize), Point(-1, -1) ); 
	//erode(binaryImageTmp ,binaryImageTmp , elementForErode );
	//dilate(binaryImageTmp ,binaryImageTmp , elementForDilate);

	separateNumsByContour( binaryImageTmp ,boundingRectsForContour);

	
    //vector<Rect> boundingRectsForContour;
	fineSeparateByContourAnalyse(boundingRectsForContour,boundingRectsForContour);


	/// imshow the fine separate nums...
#if 0

	for (int i=0; i<boundingRectsForContour.size(); i++)
	{
		//boundingRectsForContour[i] = boundingRect(filterContours[i]);
		//boundingRectsXPosition[i] =  boundingRectsForContour[i].x;
		rectangle(grayImage,boundingRectsForContour[i],Scalar(0, 0, 0));

	}
	imshow("fine coutour filled with BoundingRect",grayImage);

#endif


	vector<Mat> numImages;
	numImages.resize( boundingRectsForContour.size());
	//extractTheNumAndResize(Mat grayImage, vector<Mat> &numImages,const vector<Rect> &boundingRectsForContour );
	//extractTheNumAndResize(grayImage, numImages,boundingRectsForContour );
	Mat binaryImageInv;
	//double thresh_otsu = 0.0;
	thresh_otsu = threshold(grayImage, binaryImageInv,  0, 255, CV_THRESH_BINARY|CV_THRESH_OTSU);
	//thresh_otsu = threshold(grayImage, binaryImage,  0, 255, CV_THRESH_BINARY_INV|CV_THRESH_OTSU);
	extractTheNumAndResize(binaryImageInv, numImages,boundingRectsForContour );


	//HoG detection
#if 1



#pragma region HoG Parameters
	
	// for display Hog Features.
	//int defaultBlockSize = 21; 	 
	//int defaultCellSize = defaultBlockSize/2;  

	int defaultBlockSize = 21; 	 
	int defaultCellSize = defaultBlockSize/3;  //one block of 3*3 cell is best as paper said 
	int defaultBlockStride = defaultCellSize ;	
	int defaultBinSize = 9;
	int defaultImageSize = 28;
	//parameters of HOGDescriptor 
	Size winSize = Size(defaultImageSize,defaultImageSize);		// size of parking lot image is 128*96
	Size blockSize = Size(defaultBlockSize,defaultBlockSize);
	Size blockStride =Size(defaultBlockStride,defaultBlockStride);
	Size cellSize = Size(defaultCellSize,defaultCellSize);
	int nbins = defaultBinSize;
	Size winStride = Size(defaultImageSize,defaultImageSize);
	Size padding = Size(0,0);   // 会影响descriptors.size()的尺寸
	// construct hogDescriptor
	cv::HOGDescriptor hogDescriptor(winSize, blockSize, blockStride, cellSize, nbins);



#pragma endregion HoG Parameters

	vector<Point>locs;
	vector<float>  HoGfeatures;	
	hogDescriptor.compute(grayImage, HoGfeatures, winStride, padding, locs);	


#endif

	string svmModelFile = "mergeHogFeatures_RegularBinaryHoG.txt.model";
	struct svm_model* svmModels = svm_load_model(svmModelFile.c_str());

	int HoGfeaturesVecLength = 324;
	svm_node* _x = (struct svm_node *) malloc( (HoGfeaturesVecLength+1)*sizeof(struct svm_node) );
	double prob_estimates[10] = {0.0};
	vector<int> numRecognitionResult;
	numRecognitionResult.resize(numImages.size());
	for (int i=0; i<numImages.size(); i++)
	{
		hogDescriptor.compute(numImages[i], HoGfeatures, winStride, padding, locs);
		
		ConvertToLibSVMFormat(HoGfeatures, HoGfeatures.size(), _x);
		numRecognitionResult[i] = (int)svm_predict_probability(svmModels , _x, prob_estimates);
			 
	}


	free(_x);	
	svm_free_and_destroy_model(&svmModels);

	
	CString theString;
	CString tmpString;
	for (int i=0; i<numRecognitionResult.size(); i++)
	{
		 tmpString.Format("_%d",numRecognitionResult[i]);
		theString = theString + tmpString;
	}
	//LPTSTR lpsz =(LPTSTR)(LPCTSTR)theString;
	MessageBox(theString);

 /*
	for (int k = 0; k < this->lotCount; k++)
	{
		ConvertToLibSVMFormat(this->HoGfeatures[k], this->HoGfeatures[k].size(), _x);
		this->lotStatus[k] = (ParkingLotResult)(int)svm_predict_probability(ParkingLotHoG::svmModels[k], _x, prob_estimates);

		
		this->lotStatusProbEstimate[k][svmModels[k]->label[0]] = prob_estimates[0]; 
		this->lotStatusProbEstimate[k][svmModels[k]->label[1]] = prob_estimates[1]; 
		this->lotStatusProbEstimate[k][svmModels[k]->label[2]] = prob_estimates[2]; 

#ifdef DEBUG_ParkingLot
		printf(" %d parkingLot prob_estimates: [%d %f]  [%d %f]  [%d %f] \n",k+1, 
			svmModels[k]->label[0],prob_estimates[0], 
			svmModels[k]->label[1],prob_estimates[1],
			svmModels[k]->label[2],prob_estimates[2]);
#endif 
	}*/

	

	//vector<Mat> numImages;
	//numImages.resize( boundingRectsForContour.size());
	////extractTheNumAndResize(Mat grayImage, vector<Mat> &numImages,const vector<Rect> &boundingRectsForContour );
	////extractTheNumAndResize(grayImage, numImages,boundingRectsForContour );
	//Mat binaryImageInv;
	//threshold(grayImage, binaryImageInv,  220, 255, CV_THRESH_BINARY);
	//extractTheNumAndResize(binaryImageInv, numImages,boundingRectsForContour );
}

#endif