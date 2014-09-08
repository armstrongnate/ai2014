#ifndef _ENVIRONMENTDISPLAY_H_
#define _ENVIRONMENTDISPLAY_H_

namespace ai
{
  namespace Agent
  {
    class Environment;
    
    class EnvironmentDisplay
    {
    public:
      EnvironmentDisplay(Environment *env, int width, int height);
      EnvironmentDisplay(Environment *env, int width, int height, bool do_not_init);
      virtual ~EnvironmentDisplay();
      virtual void Redraw(Environment *env);
      virtual void Redraw();
      
      void SetColor(float *material);
      void SetEnv(Environment *env_in);
      Environment * GetEnv() const;
      
      void DrawText(int x, int y, char *str);
      void DrawText(float x, float y, char *str);
      
      void DrawLine(int x1, int y1, int x2, int y2);
      void DrawLine(float x1, float y1, float x2, float y2);
      
      void DrawCircle(int x1, int y1, int radius);
      void DrawCircle(float x1, float y1, float radius);
      
      void DrawX(float x1, float y1, float radius);
      void DrawO(float x1, float y1, float radius);
      
      void DrawRectangle(int x1, int y1, int x2, int y2);
      void DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3);

      void DrawBox(float x1, float y1, float x2, float y2);
      
    protected:
      bool Init(int width_in, int height_in, char *title_in);
      int window;
      int width;
      int height;
      Environment *env_cache;
    private:
    };
  }
}

#endif /* _ENVIRONMENTDISPLAY_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
