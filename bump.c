#include "saint-venant.h"
#include "view.h"

#define LEVEL 8

event init(t=0){
  foreach(){
    h[] = 0.1 + 1.*exp(-200.*(x*x + y*y));
  }
}

event graphs(i++){
  stats s = statsf(h);
  fprintf(stderr,"%g %g %g\n",t,s.min,s.max);
}

event images (t += 4./300.) {
  output_ppm(h,linear = true);
  scalar l[];
  foreach()
    l[] = level;

  view (tx = 0, ty = 0,width = 1200, height = 1200);
  clear();
  draw_vof("l");
  squares("h",linear = true,spread = 10);
  box();
  static FILE * fp = popen ("$BASILISK/ppm2mp4 grid.mp4", "w");
  save (fp=fp);
}
event end (t=4){
  printf("i = %d t = %g\n",i,t);
}
event adapt(i++){
  adapt_wavelet ({h}, (double []){4e-3}, maxlevel = LEVEL);
}
int main(){
  origin(-0.5,-0.5);
  init_grid(1 << LEVEL);
  run();
}
