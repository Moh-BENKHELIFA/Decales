#include "constraints.h"
#include <iostream>
#include <map>

int costFactor = 1;

Constraints::Constraints()
{


}

bool Constraints::isInsideTheImage(int i,int j, int w, int h){
    return i>=0 and i<w &&  j>=0 and j<h;
}


pse_res_t Constraints::gamut_constratint(const pse_eval_ctxt_t *, const pse_eval_coordinates_t *eval_coords, pse_eval_relshps_t *eval_relshps, pse_real_t *costs)
{
    assert(eval_relshps->count == 1);
    const struct pse_eval_relshp_data_t* data = eval_relshps->data[0];

    auto gamut = MyDecalSolver::mygamut;


    size_t height = gamut->getIHeight();
    size_t width  = gamut->getIWidth();
//    std::cout<<"size of coords:"<<sizeof(eval_coords->coords)<<std::endl;
//    std::cout<<"POINTS COUNT:::: "<<data->ppoints_count<<std::endl;

//    for(int i=0; i<sizeof(eval_coords->coords);i++){
//        std::cout<<"--------"<<i<<"--------"<<std::endl;
//        std::cout<<"x: "<<eval_coords->coords[i*2+0]<<std::endl;
//        std::cout<<"y: "<<eval_coords->coords[i*2+1]<<std::endl;

//    }

    for(size_t i = 0; i < data->ppoints_count; ++i) {
        costs[i] = 0;

        const pse_ppoint_id_t ppidx = data->ppoints[i];
        const pse_real_t x = eval_coords->coords[i*2+0];
        const pse_real_t y = eval_coords->coords[i*2+1];

        if((ppidx ==4)){
//            std::cout<<"-----------THE BEGINING-----------"<<std::endl;
//            std::cout<<"x: "<<x<<std::endl;
//            std::cout<<"y: "<<y<<std::endl;
//            std::cout<<"width: "<<width<<std::endl;
        }

        int m = int(floor(x-2.5) + 1); //floor = arrondi au plus petit
        int n = int(floor(y-2.5) + 1);

        // compute cost for out of gamut positions
        auto computeCost = [](double distance) {
          const double stepValue = 10; // distance between the decale and the gamut after repositionning
          return costFactor * (stepValue + distance );
        };

        double signedDistance = 0.0;

        auto getGamutValue = [gamut](int u, int v, double xx, double yy ){
            double result = 0.;
            if ( u == 0 or v == 0) {
                result = double(gamut->getDistanceField()->eval(u,v));
            }
            else{
                result =( (u-xx)    *( ((v-yy)     * gamut->getDistanceField()->eval(u-1,v-1))   +
                                       ((yy-(v-1)) * gamut->getDistanceField()->eval(u-1, v)) )) +
                        ( (xx-(u-1))*( ((v-yy)     * gamut->getDistanceField()->eval(u,v-1))     +
                                       ((yy-(v-1)) * gamut->getDistanceField()->eval(u, v))   ));
            }
            return result;
        };

        if(isInsideTheImage(m,n,int(width),int(height))) {
            std::map<pse_ppoint_id_t, DecaleScalarField2D*>::iterator it;
            it = MyDecalSolver::mydecalsmap.find(ppidx);
            signedDistance = std::max(
                        0.0,
                        getGamutValue(m, n, x, y ) +
                        MyDecalSolver::mydecalsmap.at(it->first)->getSizey() // radius
                                      );
            costs[i] = ( signedDistance > 0. ) ? computeCost( signedDistance ) : 0.0;
            if((ppidx ==4) and costs[i] != 0){
                std::cout<<":::::: THE GAMUT 1"<<std::endl;
            }
        }else{
            // 1. get value on the boundary of distance field
            {
                int mPrime, nPrime;

                if(m >= int(width))  mPrime = int(width) - 1;
                else if(m < 0)  mPrime = 0;
                else            mPrime = m;
                if(n >= int(height)) nPrime = int(height) - 1;
                else if(n < 0)  nPrime = 0;
                else            nPrime = n;

                signedDistance = gamut->getDistanceField()->eval(mPrime,nPrime);
            }

            // 2. add distance to boundary
            double distToBoundary = 0.;
            if(y < 0 and x > 0 and x <= width){//top
                distToBoundary = y;
                if((ppidx ==4)){
                    std::cout<<"here 1"<<std::endl;
                    std::cout<<"x: "<<x<<std::endl;
                    std::cout<<"y: "<<y<<std::endl;
                    std::cout<<"width: "<<width<<std::endl;
                }
            }else if(y >=height and x > 0 and x <= width){//bottom
                distToBoundary = y - height;
                if((ppidx ==4)){
                    std::cout<<"here 2"<<std::endl;
                    std::cout<<"x: "<<x<<std::endl;
                    std::cout<<"y: "<<y<<std::endl;
                    std::cout<<"width: "<<width<<std::endl;
                    std::cout<<"height; "<<height<<std::endl;
                }
            }else if(x < 0 and y > 0 and y <= height){//left
                distToBoundary = x;
                if((ppidx ==4)){
                    std::cout<<"here 3"<<std::endl;
                    std::cout<<"x: "<<x<<std::endl;
                    std::cout<<"y: "<<y<<std::endl;
                    std::cout<<"height: "<<height<<std::endl;

                }
            }else if(x >=width and y > 0 and y <= height){//right
                distToBoundary = x - width;
                if((ppidx ==4)){
                    std::cout<<"here 4"<<std::endl;
                    std::cout<<"x: "<<x<<std::endl;
                    std::cout<<"y: "<<y<<std::endl;
                    std::cout<<"width: "<<width<<std::endl;
                    std::cout<<"height: "<<height<<std::endl;
                }
            }else if(x < 0 and y < 0){//top left
                distToBoundary = std::sqrt(std::pow(x-0, 2) + std::pow(y-0, 2));
                if((ppidx ==4)){
                    std::cout<<"here 5"<<std::endl;
                    std::cout<<"x: "<<x<<std::endl;
                    std::cout<<"y: "<<y<<std::endl;
                }
            }else if(x >=width and y < 0){//top right
                distToBoundary = std::sqrt(std::pow(x-width, 2) + std::pow(y-0, 2));
                if((ppidx ==4)){
                    std::cout<<"here 6"<<std::endl;
                    std::cout<<"x: "<<x<<std::endl;
                    std::cout<<"y: "<<y<<std::endl;
                    std::cout<<"width: "<<width<<std::endl;

                }
            }else if(x < 0 and y >= height){//bottom left
                distToBoundary = std::sqrt(std::pow(x-0, 2) + std::pow(y-height, 2));
                if((ppidx ==4)){
                    std::cout<<"here 7"<<std::endl;
                    std::cout<<"x: "<<x<<std::endl;
                    std::cout<<"y: "<<y<<std::endl;
                    std::cout<<"height: "<<height<<std::endl;
                }
            }else if(x >=width and y >= height){//bottom right
                distToBoundary = std::sqrt(std::pow(x-width, 2) + std::pow(y-height, 2));
                if((ppidx ==4)){
                    std::cout<<"here 8"<<std::endl;
                    std::cout<<"x: "<<x<<std::endl;
                    std::cout<<"y: "<<y<<std::endl;
                    std::cout<<"width"<<width<<std::endl;
                    std::cout<<"height: "<<height<<std::endl;
                }
            }else{
                std::cout<<"outside of the mat "<<std::endl;
            }
            costs[i] += computeCost( signedDistance + distToBoundary );

            if((ppidx ==4) and costs[i] != 0){
                std::cout<<":::::: THE GAMUT 2"<<std::endl;
            }
        }

//        if((ppidx ==4) and costs[i] != 0){
//            std::cout<<":::::: THE GAMUT 3"<<std::endl;
//        }


    }
    return RES_OK;
}

pse_res_t Constraints::min_dist_constratint(const pse_eval_ctxt_t *eval_ctxt,
                                            const pse_eval_coordinates_t *eval_coords,
                                            pse_eval_relshps_t *eval_relshps,
                                            pse_real_t *costs)
{
    size_t i;
    (void)eval_ctxt;

    for(i = 0; i < eval_relshps->count; ++i) {
        const struct pse_eval_relshp_data_t* data = eval_relshps->data[i];
        assert(data->ppoints_count == 2);

        const pse_ppoint_id_t ppidx1 = data->ppoints[0];
        const pse_ppoint_id_t ppidx2 = data->ppoints[1];

        const pse_real_t x1 = eval_coords->coords[ppidx1*2+0];
        const pse_real_t y1 = eval_coords->coords[ppidx1*2+1];

        const pse_real_t x2 = eval_coords->coords[ppidx2*2+0];
        const pse_real_t y2 = eval_coords->coords[ppidx2*2+1];

        double dist = std::max(std::abs(x2-x1), std::abs(y2-y1));

//        double dist = std::sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));

        std::map<pse_ppoint_id_t, DecaleScalarField2D*>::iterator it1;
        std::map<pse_ppoint_id_t, DecaleScalarField2D*>::iterator it2;
        it1 = MyDecalSolver::mydecalsmap.find(ppidx1);
        it2 = MyDecalSolver::mydecalsmap.find(ppidx2);

        int id1 = it1->first;
        int id2 = it2->first;

        double rx1 = MyDecalSolver::mydecalsmap.at(it1->first)->getSizex();
        double rx2 = MyDecalSolver::mydecalsmap.at(it2->first)->getSizex();
        double ry1 = MyDecalSolver::mydecalsmap.at(it1->first)->getSizey();
        double ry2 = MyDecalSolver::mydecalsmap.at(it2->first)->getSizey();

        double distancex = abs(x2-x1)-rx1-rx2;
        double distancey = abs(y2-y1)-ry1-ry2;

        double distance = std::max(distancex, distancey);


//        if(distancex <= 1 && distancex >=0)
//                distancex = -1;

//        if(distancey <= 1 && distancey >=0)
//                distancey = -1;

        if(distance <= 1 && distance >=0)
                distance= -1;

        costs[i] = costFactor * std::min(00.0, distance);
//        costs[i] =0;

//        if(costs[i]!= 0)
//            std::cout<<"COSTS: "<<costs[i]<<std::endl;

        if(id1==1 && id2==3 ){
//            std::cout<<"id2: " <<id2<<std::endl;
//            std::cout<<"DISTANCE: " <<dist-r1-r2<<std::endl;
//            std::cout<<"DISTANCE2: " <<distance<<std::endl;
//            std::cout<<"COSTS: "<<costs[i]<<std::endl;
        }

        if(id1==0 && id2 ==2){
//            std::cout<<"------Minimum constraint id0------"<<std::endl;
//            std::cout<<"dist:"<<dist<<std::endl;
//            std::cout<<"distx: "<<std::abs(x2-x1)<<std::endl;
//            std::cout<<"disty: "<<std::abs(y2-y1)<<std::endl;
//            std::cout<<"distance X: "<<distancex<<std::endl;
//            std::cout<<"distance Y: "<<distancey<<std::endl;
//            std::cout<<"Size x: "<<rx1<<std::endl;
//            std::cout<<"Size y: "<<ry1<<std::endl;




        }

//        if((id1==4 or id2 ==4) and costs[i] != 0){
//           // std::cout<<":::::: THE MIN"<<std::endl;
//        }


    }


    return RES_OK;

}

//pse_res_t Constraints::max_dist_constratint(const pse_eval_ctxt_t *eval_ctxt,
//                                            const pse_eval_coordinates_t *eval_coords,
//                                            pse_eval_relshps_t *eval_relshps,
//                                            pse_real_t *costs){
//    size_t i;
//    (void)eval_ctxt;

//    for(i = 0; i < eval_relshps->count; ++i) {
////    for(i = 0; i < data->ppoints_count; ++i) {
//        const struct pse_eval_relshp_data_t* data = eval_relshps->data[i];
//        assert(data->ppoints_count == 2);

//        const pse_ppoint_id_t ppidx1 = data->ppoints[0];
//        const pse_ppoint_id_t ppidx2 = data->ppoints[1];

//        const pse_real_t x1 = eval_coords->coords[ppidx1*2+0];
//        const pse_real_t y1 = eval_coords->coords[ppidx1*2+1];

//        const pse_real_t x2 = eval_coords->coords[ppidx2*2+0];
//        const pse_real_t y2 = eval_coords->coords[ppidx2*2+1];

//        //std::cout<<i<<"relship: "<<ppidx1<<"-"<<ppidx2<<std::endl;
//        double dist = std::sqrt(std::pow(x2-x1, 2) + std::pow(y2-y1, 2));//L2 dist;

//        //double dist = std::max(std::abs(x2-x1), std::abs(y2-y1));//L1 dist

//        std::map<pse_ppoint_id_t, DecaleScalarField2D*>::iterator it1;
//        std::map<pse_ppoint_id_t, DecaleScalarField2D*>::iterator it2;
//        it1 = MyDecalSolver::mydecalsmap.find(ppidx1);
//        it2 = MyDecalSolver::mydecalsmap.find(ppidx2);

//        int id1 = it1->first;
//        int id2 = it2->first;

////        std::cout<<"MAX DISTANC: "<<id1<<" : "<<id2<<std::endl;


//        double maxDist = 150; //if <150 collision doesn't work
//        double f =  std::max(0.0, dist - maxDist);

//        //2 decals relation

//        //C
////        if( id1 == 0 and id2 == 1){
////            costs[i] = f;
//////            std::cout<<"dist = "<<dist - maxDist<<std::endl;
//////            std::cout<<"f = "<<f<<std::endl;


////        }else
//            costs[i] = 0;

//            if((id1==4 or id2 ==4) and costs[i] != 0){
//                std::cout<<":::::: THE MAX"<<std::endl;
//            }

////        costs[i] *= costFactor;
//    }

//    return RES_OK;
//}



pse_res_t Constraints::max_dist_constratint(const pse_eval_ctxt_t *eval_ctxt,
                                            const pse_eval_coordinates_t *eval_coords,
                                            pse_eval_relshps_t *eval_relshps,
                                            pse_real_t *costs){
    size_t i;
    (void)eval_ctxt;

    for(i = 0; i < eval_relshps->count; ++i) {
        const struct pse_eval_relshp_data_t* data = eval_relshps->data[i];
        assert(data->ppoints_count == 2);

        const pse_ppoint_id_t ppidx1 = data->ppoints[0];
        const pse_ppoint_id_t ppidx2 = data->ppoints[1];

        const pse_real_t x1 = eval_coords->coords[ppidx1*2+0];
        const pse_real_t y1 = eval_coords->coords[ppidx1*2+1];

        const pse_real_t x2 = eval_coords->coords[ppidx2*2+0];
        const pse_real_t y2 = eval_coords->coords[ppidx2*2+1];

        double dist = std::sqrt(std::pow(x2-x1, 2) + std::pow(y2-y1, 2));//L2 dist;

        //double dist = std::max(std::abs(x2-x1), std::abs(y2-y1));//L1 dist

        std::map<pse_ppoint_id_t, DecaleScalarField2D*>::iterator it1;
        std::map<pse_ppoint_id_t, DecaleScalarField2D*>::iterator it2;
        it1 = MyDecalSolver::mydecalsmap.find(ppidx1);
        it2 = MyDecalSolver::mydecalsmap.find(ppidx2);

        int id1 = it1->first;
        int id2 = it2->first;

        double maxDist = 150; //if <150 collision doesn't work
        double f =  std::max(0.0, dist - maxDist);

//        if( id1 == 0 and id2 == 2){
//            costs[i] = f;
//        }ELSE
            costs[i] = 0;

        costs[i] *= costFactor;
    }

    return RES_OK;
}

//pse_res_t Constraints::alignment_constraint(const pse_eval_ctxt_t *eval_ctxt,
//                                            const pse_eval_coordinates_t *eval_coords,
//                                            pse_eval_relshps_t *eval_relshps,
//                                            pse_real_t *costs){

//    size_t i;
//    (void)eval_ctxt;

//    const struct pse_eval_relshp_data_t* data = eval_relshps->data[0];


////    for(i = 0; i < eval_relshps->count; ++i) {
//    for(i = 0; i < data->ppoints_count; ++i){
//           //assert(data->ppoints_count == 2);
////           const struct pse_eval_relshp_data_t* data = eval_relshps->data[i];

//           assert(eval_relshps->count == 1);

//           const pse_ppoint_id_t ppidx1 = data->ppoints[0];
//           const pse_ppoint_id_t ppidx2 = data->ppoints[1];

//           const pse_real_t x1 = eval_coords->coords[ppidx1*2+0];

//           const pse_real_t x2 = eval_coords->coords[ppidx2*2+0];
//           const pse_real_t y2 = eval_coords->coords[ppidx2*2+1];


//           double dist = std::sqrt(std::pow(x2-x1, 2));;//L2 dist;
////           double dist = std::sqrt(std::pow(x2-200, 2) + std::pow(y2-200, 2));;//L2 dist;

//           //double dist = std::max(std::abs(x2-x1), std::abs(y2-y1));//L1 dist

//           std::map<pse_ppoint_id_t, DecaleScalarField2D*>::iterator it1;
//           std::map<pse_ppoint_id_t, DecaleScalarField2D*>::iterator it2;
//           it1 = MyDecalSolver::mydecalsmap.find(ppidx1);
//           it2 = MyDecalSolver::mydecalsmap.find(ppidx2);

//           int id1 = it1->first;
//           int id2 = it2->first;

//           std::cout<<"la relation entre "<<id1<<" | "<<id2<<std::endl;

//           double maxDist = 00; //if <150 collision doesn't work
//           double f =  std::max(0.0, dist - maxDist);

//           if(id1==0 and id2 == 2){
//               costs[i] = f;
//           }else
//               costs[i] = 0;

//           costs[i] *= costFactor;
//       }

//       return RES_OK;
//}


//pse_res_t Constraints::alignment_constraint(const pse_eval_ctxt_t *eval_ctxt,
//                                            const pse_eval_coordinates_t *eval_coords,
//                                            pse_eval_relshps_t *eval_relshps,
//                                            pse_real_t *costs){

//    size_t i;
//    (void)eval_ctxt;

//    //const struct pse_eval_relshp_data_t* data = eval_relshps->data[0];


//    for(i = 0; i < eval_relshps->count; ++i) {
//   // for(i = 0; i < data->ppoints_count; ++i){
//           const struct pse_eval_relshp_data_t* data = eval_relshps->data[i];
//           //assert(data->ppoints_count == 2);

////           assert(eval_relshps->count == 1);

//           const pse_ppoint_id_t ppidx1 = data->ppoints[0];
//           const pse_ppoint_id_t ppidx2 = data->ppoints[1];

//           const pse_real_t x1 = eval_coords->coords[ppidx1*2+0];

//           const pse_real_t x2 = eval_coords->coords[ppidx2*2+0];
//          // const pse_real_t y2 = eval_coords->coords[ppidx2*2+1];


//           double dist = std::sqrt(std::pow(x2-x1, 2));;//L2 dist;
////           double dist = std::sqrt(std::pow(x2-200, 2) + std::pow(y2-200, 2));;//L2 dist;

//           //double dist = std::max(std::abs(x2-x1), std::abs(y2-y1));//L1 dist

//           std::map<pse_ppoint_id_t, DecaleScalarField2D*>::iterator it1;
//           std::map<pse_ppoint_id_t, DecaleScalarField2D*>::iterator it2;
//           it1 = MyDecalSolver::mydecalsmap.find(ppidx1);
//           it2 = MyDecalSolver::mydecalsmap.find(ppidx2);

//           int id1 = it1->first;
//           int id2 = it2->first;

//           double maxDist = 00; //if <150 collision doesn't work
//           double f =  std::max(0.0, dist - maxDist);

//           if(id1==0 and id2 == 2){
//               costs[i] = f;
//           }else
//               costs[i] = 0;

//           costs[i] *= costFactor;

//           if((id1==4 or id2 ==4) and costs[i] != 0){
//               std::cout<<"NON MAIS OH C'EST QUOI CE SCANDALE LA JE SUIS PAS SUPPOSE BOUGER"<<std::endl;
//           }
//       }

//       return RES_OK;
//}


//pse_res_t Constraints::vertical_line_alignment_constraint(const pse_eval_ctxt_t *eval_ctxt,
//                                            const pse_eval_coordinates_t *eval_coords,
//                                            pse_eval_relshps_t *eval_relshps,
//                                            pse_real_t *costs){

//    size_t i;
//    (void)eval_ctxt;

//    const struct pse_eval_relshp_data_t* data = eval_relshps->data[0];


//    for(i = 0; i < eval_relshps->count; ++i) {
////    for(i = 0; i < data->ppoints_count; ++i){
//           assert(data->ppoints_count == 2);
////           const struct pse_eval_relshp_data_t* data = eval_relshps->data[i];

////           assert(eval_relshps->count == 1);

//                   costs[i] = 0;

//           const pse_ppoint_id_t ppidx = data->ppoints[i];

//           const pse_real_t x = eval_coords->coords[i*2+0];
//           const pse_real_t y = eval_coords->coords[i*2+1];





//            //ppidx1 determine le decal auquel c'est aligné
//           const pse_ppoint_id_t ppidx1 = data->ppoints[3];
//           //const pse_ppoint_id_t ppidx2 = data->ppoints[1];

//           const pse_real_t x1 = eval_coords->coords[ppidx1*2+0];

////           const pse_real_t x2 = eval_coords->coords[ppidx2*2+0];
////           const pse_real_t y2 = eval_coords->coords[ppidx2*2+1];


//           double dist = std::sqrt(std::pow(x-x1, 2));;//L2 dist;
////           double dist = std::sqrt(std::pow(x2-200, 2) + std::pow(y2-200, 2));;//L2 dist;

//           //double dist = std::max(std::abs(x2-x1), std::abs(y2-y1));//L1 dist

//           std::map<pse_ppoint_id_t, DecaleScalarField2D*>::iterator it1;
//           std::map<pse_ppoint_id_t, DecaleScalarField2D*>::iterator it2;
//           it1 = MyDecalSolver::mydecalsmap.find(ppidx1);
//           it2 = MyDecalSolver::mydecalsmap.find(ppidx);

//           int id1 = it1->first;
//           int id2 = it2->first;

//           double maxDist = 00; //if <150 collision doesn't work
//           double f =  std::max(0.0, dist - maxDist);

//          // std::cout<<"la relation entre "<<id1<<" | "<<id2<<std::endl;


//           if(id1==3 and id2 == 2){
//               costs[i] = f;
//           }else if(id1==3 and id2 == 1){
//               costs[i] = f;
//           }else
//               costs[i] = 0;

//           costs[i] *= costFactor;

//           if((id1==4 or id2 ==4) and costs[i] != 0){
//               std::cout<<":::::: THE ALIGNMENT"<<std::endl;
//           }

//       }


//       return RES_OK;
//}

//PerRelation
//pse_res_t Constraints::vertical_alignment_constraint(const pse_eval_ctxt_t *eval_ctxt,
//                                            const pse_eval_coordinates_t *eval_coords,
//                                            pse_eval_relshps_t *eval_relshps,
//                                            pse_real_t *costs){

//    size_t i;
//    (void)eval_ctxt;

////    const struct pse_eval_relshp_data_t* data = eval_relshps->data[0];


//    for(i = 0; i < eval_relshps->count; ++i) {
//        const struct pse_eval_relshp_data_t* data = eval_relshps->data[i];
//        assert(data->ppoints_count == 2);

//        costs[i] = 0;

//        //ppidx1 is the aligned decale reference
//        const pse_ppoint_id_t ppidx1 = data->ppoints[0];
//        const pse_ppoint_id_t ppidx2 = data->ppoints[1];

//        const pse_real_t x1 = eval_coords->coords[ppidx1*2+0];
//        const pse_real_t x2 = eval_coords->coords[ppidx2*2+0];

//        double dist = std::sqrt(std::pow(x2-x1, 2));;//L2 dist;

//        std::map<pse_ppoint_id_t, DecaleScalarField2D*>::iterator it1;
//        std::map<pse_ppoint_id_t, DecaleScalarField2D*>::iterator it2;
//        it1 = MyDecalSolver::mydecalsmap.find(ppidx1);
//        it2 = MyDecalSolver::mydecalsmap.find(ppidx2);

//        int id1 = it1->first;
//        int id2 = it2->first;

//        double maxDist = 00;  //float alignment value
//        double f =  std::max(0.0, dist - maxDist);

////        if(id1==2 and id2 == 3){
////           costs[i] = f;
////        }else if(id1==1 and id2 == 2){
////           costs[i] = f;
////        }else
//           costs[i] = 0;

//        costs[i] *= costFactor;
//       }


//       return RES_OK;
//}


//pse_res_t Constraints::horizontal_alignment_constraint(const pse_eval_ctxt_t *eval_ctxt,
//                                            const pse_eval_coordinates_t *eval_coords,
//                                            pse_eval_relshps_t *eval_relshps,
//                                            pse_real_t *costs){

//    size_t i;
//    (void)eval_ctxt;

////    const struct pse_eval_relshp_data_t* data = eval_relshps->data[0];


//    for(i = 0; i < eval_relshps->count; ++i) {
//        const struct pse_eval_relshp_data_t* data = eval_relshps->data[i];
//        assert(data->ppoints_count == 2);

//        costs[i] = 0;

//        //ppidx1 is the aligned decale reference
//        const pse_ppoint_id_t ppidx1 = data->ppoints[0];
//        const pse_ppoint_id_t ppidx2 = data->ppoints[1];

//        const pse_real_t y1 = eval_coords->coords[ppidx1*2+1];
//        const pse_real_t y2 = eval_coords->coords[ppidx2*2+1];

//        double dist = std::sqrt(std::pow(y2-y1, 2));;//L2 dist;

//        std::map<pse_ppoint_id_t, DecaleScalarField2D*>::iterator it1;
//        std::map<pse_ppoint_id_t, DecaleScalarField2D*>::iterator it2;
//        it1 = MyDecalSolver::mydecalsmap.find(ppidx1);
//        it2 = MyDecalSolver::mydecalsmap.find(ppidx2);

//        int id1 = it1->first;
//        int id2 = it2->first;

//        double maxDist = 00;  //float alignment value
//        double f =  std::max(0.0, dist - maxDist);

////        if(id1==1 and id2 == 3){
////           costs[i] = f;
////        }else
//           costs[i] = 0;

//        costs[i] *= costFactor;
//       }


//       return RES_OK;
//}


pse_res_t Constraints::vertical_line_alignment_constraint(const pse_eval_ctxt_t *eval_ctxt,
                                            const pse_eval_coordinates_t *eval_coords,
                                            pse_eval_relshps_t *eval_relshps,
                                            pse_real_t *costs){

    size_t i;
    (void)eval_ctxt;

    const struct pse_eval_relshp_data_t* data = eval_relshps->data[0];


    for(i = 0; i < data->ppoints_count; ++i){
        assert(eval_relshps->count == 1);

        costs[i] = 0;

        const pse_ppoint_id_t ppidx = data->ppoints[i];

        const pse_real_t x = eval_coords->coords[i*2+0];
        const pse_real_t y = eval_coords->coords[i*2+1];

        int x_line= 600;
        double dist = std::sqrt(std::pow(x-x_line, 2));;//L2 dist;
        //           double dist = std::sqrt(std::pow(x2-200, 2) + std::pow(y2-200, 2));;//L2 dist;

        //double dist = std::max(std::abs(x2-x1), std::abs(y2-y1));//L1 dist

        std::map<pse_ppoint_id_t, DecaleScalarField2D*>::iterator it1;
        it1 = MyDecalSolver::mydecalsmap.find(ppidx);

        int id1 = it1->first;

        double maxDist = 00; //if <150 collision doesn't work
        double f =  std::max(0.0, dist - maxDist);

        // std::cout<<"la relation entre "<<id1<<" | "<<id2<<std::endl;


//        if(id1==3){
//            costs[i] = f;
//        }else
            costs[i] = 0;

        costs[i] *= costFactor;


       }


       return RES_OK;
}


pse_res_t Constraints::horizontal_line_alignment_constraint(const pse_eval_ctxt_t *eval_ctxt,
                                            const pse_eval_coordinates_t *eval_coords,
                                            pse_eval_relshps_t *eval_relshps,
                                            pse_real_t *costs){

    size_t i;
    (void)eval_ctxt;

    const struct pse_eval_relshp_data_t* data = eval_relshps->data[0];

//    std::cout<<"POINTS COUNT:::: <<"<<data->ppoints_count<<std::endl;

    for(i = 0; i < data->ppoints_count; ++i){
        assert(eval_relshps->count == 1);


        costs[i] = 0;

        const pse_ppoint_id_t ppidx = data->ppoints[i];



        const pse_real_t y = eval_coords->coords[i*2+1];

        //Virtual line alignment
//      int y_line= 500;

        //Align to a decale
        int y_line = eval_coords->coords[3*2+1];

        double dist = std::sqrt(std::pow(y-y_line, 2))/2;;//L2 dist;

        std::map<pse_ppoint_id_t, DecaleScalarField2D*>::iterator it1;
        it1 = MyDecalSolver::mydecalsmap.find(ppidx);

        int id1 = it1->first;

        double maxDist = 00;
        double f =  std::max(0.0, dist - maxDist);

        if(id1==0){
            costs[i] = f;
        }else
            costs[i] = 0;

        costs[i] *= costFactor;


       }


       return RES_OK;
}


pse_res_t Constraints::fixed_position_constraint(const pse_eval_ctxt_t *eval_ctxt,
                                            const pse_eval_coordinates_t *eval_coords,
                                            pse_eval_relshps_t *eval_relshps,
                                            pse_real_t *costs){

    size_t i;
    (void)eval_ctxt;

    const struct pse_eval_relshp_data_t* data = eval_relshps->data[0];


    for(i = 0; i < data->ppoints_count; ++i){
        assert(eval_relshps->count == 1);

        costs[i] = 0;

        const pse_ppoint_id_t ppidx = data->ppoints[i];

        const pse_real_t x = eval_coords->coords[i*2+0];
        const pse_real_t y = eval_coords->coords[i*2+1];

        int x_line = 700;
        int y_line = 500;

        double dist = std::sqrt(std::pow(x-x_line, 2) + std::pow(y-y_line, 2));;//L2 dist;

        std::map<pse_ppoint_id_t, DecaleScalarField2D*>::iterator it1;
        it1 = MyDecalSolver::mydecalsmap.find(ppidx);

        int id1 = it1->first;

        double maxDist = 00;
        double f =  std::max(0.0, dist - maxDist);

//        if(id1==0){
//            costs[i] = f;
//        }else
            costs[i] = 0;

        costs[i] *= costFactor;

     }


       return RES_OK;
}

