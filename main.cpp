#include <iostream>
#include <opencv2/opencv.hpp>
#include <random>
#include <vector>

constexpr int rows = 70;
constexpr int cols = 70;

constexpr int coef = 10;

bool* lives[2];

cv::Vec3b fore_color, back_color;

std::vector<cv::Point2f> click_buffer;


void mouse_handler(int event, int x, int y, int flags, void *userdata)
{
	if (event == cv::EVENT_LBUTTONDOWN)
	{
		std::cout << "Left button of the mouse is clicked - position (" << x << ", "
				  << y << ")" << '\n';
		click_buffer.emplace_back(x, y);
	}
}


void randomize(bool* table, float probability)
{
	std::random_device rd;
	std::default_random_engine rng {rd()};
	std::uniform_real_distribution<float> r(0.f, 1.f);

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			table[i * cols + j] = r(rng) < probability;
		}
	}
}


void example()
{

}


bool get_value(const bool* p, int x, int y)
{
	if (0 <= x && x < rows && 0 <= y && y < cols)
	{
		return p[x * cols + y];
	}
	else
	{
		return false;
	}
}


bool life_rule(bool* table, int x, int y)
{
	int cnt = get_value(table, x, y) ? -1 : 0;
	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			if (get_value(table, x + i, y + j))
			{
				cnt++;
			}
		}
	}
	if (cnt == 2)
	{
		return get_value(table, x, y);
	}
	else if (cnt == 3)
	{
		return true;
	}
	else
	{
		return false;
	}
}


void next_window(bool* old_lives, bool* new_lives)
{
	for (int x = 0; x < rows; x++)
	{
		for (int y = 0; y < cols; y++)
		{
			new_lives[x * cols + y] = life_rule(old_lives, x, y);
		}
	}
}

void show_in_window(const bool* table, cv::Mat& window)
{

	for (int x = 0; x < rows; x++)
	{
		for (int y = 0; y < cols; y++)
		{
			cv::Vec3b& color = table[x * cols + y] ? fore_color : back_color;
			for (int i = 0; i < coef; i++)
			{
				for (int j = 0; j < coef; j++)
				{
					window.at<cv::Vec3b>(x * coef + i, y * coef + j) = color;
				}
			}
		}
	}
}


void initial()
{
	lives[0] = new bool[rows * cols];
	lives[1] = new bool[rows * cols];

	click_buffer.clear();

	auto sum = rows * cols;
	for (int i = 0; i < sum; i++)
	{
		lives[0][i] = lives[1][i] = false;
	}

	fore_color = cv::Vec3b(0, 181, 248);
	back_color = cv::Vec3b(0, 0, 0);
}


int main()
{
	initial();

	cv::Mat window = cv::Mat(rows * coef, cols * coef, CV_8UC3, cv::Scalar(0));
	cv::cvtColor(window, window, cv::COLOR_BGR2RGB);
	cv::namedWindow("GameOfLife", cv::WINDOW_AUTOSIZE);

	cv::setMouseCallback("GameOfLife", mouse_handler, nullptr);

//	randomize(lives[0], 0.1f);

	int key = -1, t = 0;
	while (key != 27)
	{
		show_in_window(lives[t & 1], window);
		cv::imshow("GameOfLife", window);
		do
		{
			while (!click_buffer.empty())
			{
				cv::Point2f p = *click_buffer.begin();
				click_buffer.erase(click_buffer.begin());
				int y = p.x / 10;
				int x = p.y / 10;
				lives[t & 1][x * cols + y] = true;
			}
			show_in_window(lives[t & 1], window);
			cv::imshow("GameOfLife", window);
			key = cv::waitKey(20);
		} while (key != 13 && key != 27);
		next_window(lives[t & 1], lives[1 - (t & 1)]);
		t++;
	}
	return 0;
}
