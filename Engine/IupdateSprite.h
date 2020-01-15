class IupdateSprite
{
private:
public:
	IupdateSprite(void);
	virtual ~IupdateSprite(void);

	virtual void load() = 0;
	virtual void update() = 0;
	virtual void destroy() = 0;
};