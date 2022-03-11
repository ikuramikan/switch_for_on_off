# include <Siv3D.hpp> // OpenSiv3D v0.6.3

class Switch_ratio
{
private:
	// 使うフォント
	Font m_font;

	// Switchがオンのとき表す変数
	String on_item;
	// Switchがオフのとき表す変数
	String off_item;

	// Switchがオンになっているかどうか
	bool switch_on;

	// Switchの描画表現
	RectF m_rect; // 土台
	RectF on_rect; // オンに対応する四角
	RectF off_rect; // オフに対応する四角
	Size m_padding = {8,4};

public:
	// 何も引数がないときのコンストラクタ
	Switch_ratio() = default;

	// 引数ありのコンストラクタ
	Switch_ratio(const String& on_item, const String& off_item, const Font& font, const Vec2& pos = { 0,0 })
		:m_font{ font }, on_item{ on_item }, off_item{ off_item },switch_on{true}
	{
		m_rect = RectF{ pos, 0, (m_font.height() + m_padding.y * 6) };
		// 土台部分の長方形の幅を決定する
		m_rect.w = Max(static_cast<int32>(m_font(on_item).region().w), static_cast<int32>(m_font(off_item).region().w))*2;
		m_rect.w += m_padding.x * 6;

		// オン・オフに対応する長方形を決定する。
		on_rect = RectF{ m_rect.pos + Vec2{m_padding.x, m_padding.y}, (m_rect.w-4*m_padding.x) / 2, m_rect.h-m_padding.y*2 };
		off_rect = RectF{ m_rect.pos + Vec2{m_rect.w/2+m_padding.x, m_padding.y}, (m_rect.w-4*m_padding.x) / 2, m_rect.h-m_padding.y*2 };
	}

	// 更新関数
	void update()
	{
		// スイッチが押されたらそれに対応させる
		if (on_rect.leftClicked())
		{
			switch_on = true;
		}
		if (off_rect.leftClicked())
		{
			switch_on = false;
		}
	}

	// 描画関数
	void draw() const
	{
		// 土台の描画
		m_rect.rounded(3).drawShadow(Vec2{ 2,2 }, 8, 1).draw(Palette::Aliceblue);

		// オン・オフ部分の描画
		on_rect.rounded(3).draw(switch_on?Palette::Lavender:Palette::Lightslategray);
		off_rect.rounded(3).draw(switch_on?Palette::Lightslategray:Palette::Lavender);

		// マウスが置かれているボタンを囲む
		if (on_rect.mouseOver()&&switch_on==false)
		{
			on_rect.rounded(3).drawFrame(0, 2, Palette::Aquamarine);
		}
		if (off_rect.mouseOver()&&switch_on==true)
		{
			off_rect.rounded(3).drawFrame(0, 2, Palette::Aquamarine);
		}

		// 文字の描画
		m_font(on_item).drawAt(on_rect.center(), Palette::Black);
		m_font(off_item).drawAt(off_rect.center(), Palette::Black);
	}

	// switch_onを取得する関数
	bool get_switch() const
	{
		return switch_on;
	}

	// swichの中身を取得する関数
	String get_item(bool on) const
	{
		if (on)
		{
			return on_item;
		}
		else
		{
			return off_item;
		}
	}

	// スイッチの位置変更のための関数
	void setPos(const Vec2& pos)
	{
		m_rect.setPos(pos);
	}
};

void Main()
{
	Scene::SetBackground(Palette::White);

	const Font font{ 24 };
	String first_item = U"ON";
	String second_item = U"OFF";

	Switch_ratio sr = { first_item, second_item, font, Vec2{100,100} };

	while (System::Update())
	{
		sr.update();
		sr.draw();

		if (sr.get_switch())
		{
			Scene::SetBackground(Palette::Red);
		}
		else
		{
			Scene::SetBackground(Palette::Blue);
		}
	}
}

