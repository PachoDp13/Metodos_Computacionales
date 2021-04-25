#include <../inc/Anim.h>


Anim::Anim(){

}

Anim::Anim(double lim_):lim(lim_){

}

void Anim::SetLim(double lim_){
	lim = lim_;
}

Anim::~Anim(){
	
}

// Methods
void Anim::NewAnim(){
  limits = "[-"+std::to_string(lim)+":"+std::to_string(lim)+"]";
  std::cout<<"set terminal gif animate delay 1" <<std::endl;
  std::cout<<"set output 'Orbitas.gif'"<<std::endl;
  std::cout<<"unset key"<<std::endl;
  std::cout<<"set xrange "+limits<<std::endl;
  std::cout<<"set yrange "+limits<<std::endl;
  std::cout<<"set grid"<<std::endl;
  std::cout<<"set size ratio -1"<<std::endl;
  std::cout<<"set parametric"<<std::endl;
  std::cout<<"set trange [0:10]"<<std::endl;
  std::cout<<"set isosamples 12"<<std::endl;
}

void Anim::StartLine(){

  std::cout<<"plot 0,0";

}


void Anim::EndLine(){
	std::cout<<std::endl;
}
