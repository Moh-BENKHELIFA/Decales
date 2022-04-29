#include "mydecalsolver.h"
#include <iostream>
#include "constraints.h"
#include "../GUI-Decale/QWidgetMyDecale.h"


MyDecalSolver::MyDecalSolver() :  GenericSolver(){
    std::cout<<"mysolver: constructor"<<std::endl;
}
std::map<pse_ppoint_id_t, DecaleScalarField2D*> MyDecalSolver::mydecalsmap;
GamutField2D* MyDecalSolver::mygamut;

void MyDecalSolver::setDecales(const VectorOfDecaleFields &decales){
    this->decales = decales;
    std::cout<<"mysolver: setting decals test "<<decales[0]->getCornerX()<<std::endl;
}

void MyDecalSolver::setGamut(GamutField2D *gamut)
{
    this->mygamut = gamut;
}

void MyDecalSolver::internal_preupdate_assignconstraints()
{

    gamut_cosntr_ID = fp.size();
    fp.push_back( PSE_RELSHP_COST_FUNC_PARAMS_NULL);
    fids.push_back(PSE_RELSHP_COST_FUNC_ID_INVALID_);
    fp.back().compute = Constraints::gamut_constratint;
    fp.back().cost_arity_mode = PSE_COST_ARITY_MODE_PER_POINT;
    fp.back().costs_count = 1;
    fp.back().expected_pspace = r2_uid;

    //vertical line alignement constr
    vertical_line_alignment_constr_ID = fp.size();
    fp.push_back( PSE_RELSHP_COST_FUNC_PARAMS_NULL);
    fids.push_back(PSE_RELSHP_COST_FUNC_ID_INVALID_);
    fp.back().compute = Constraints::vertical_line_alignment_constraint;
    fp.back().cost_arity_mode = PSE_COST_ARITY_MODE_PER_POINT;
    fp.back().costs_count = 1;
    fp.back().expected_pspace = r2_uid;

    //horizontal line alignement constr
    horizontal_line_alignment_constr_ID = fp.size();
    fp.push_back( PSE_RELSHP_COST_FUNC_PARAMS_NULL);
    fids.push_back(PSE_RELSHP_COST_FUNC_ID_INVALID_);
    fp.back().compute = Constraints::horizontal_line_alignment_constraint;
    fp.back().cost_arity_mode = PSE_COST_ARITY_MODE_PER_POINT;
    fp.back().costs_count = 1;
    fp.back().expected_pspace = r2_uid;

    //fixed position constr
    fixed_position_constr_ID = fp.size();
    fp.push_back( PSE_RELSHP_COST_FUNC_PARAMS_NULL);
    fids.push_back(PSE_RELSHP_COST_FUNC_ID_INVALID_);
    fp.back().compute = Constraints::fixed_position_constraint;
    fp.back().cost_arity_mode = PSE_COST_ARITY_MODE_PER_POINT;
    fp.back().costs_count = 1;
    fp.back().expected_pspace = r2_uid;

    //min dist constr
    min_dist_cosntr_ID = fp.size(); //set id number to add more constraints to the solver
    fp.push_back(PSE_RELSHP_COST_FUNC_PARAMS_NULL);
    fids.push_back(PSE_RELSHP_COST_FUNC_ID_INVALID_);
    fp.back().compute = Constraints::min_dist_constratint;
    fp.back().cost_arity_mode = PSE_COST_ARITY_MODE_PER_RELATIONSHIP;
    fp.back().costs_count = 1;
    fp.back().expected_pspace = r2_uid;

    //max dist constr
    max_dist_cosntr_ID = fp.size();
    fp.push_back( PSE_RELSHP_COST_FUNC_PARAMS_NULL);//TODO what is it pushing back ?
    fids.push_back(PSE_RELSHP_COST_FUNC_ID_INVALID_);//Says that every cost function is invalid at the init?
    fp.back().compute = Constraints::max_dist_constratint;//Function to call? How do you pass the parameters?
    fp.back().cost_arity_mode = PSE_COST_ARITY_MODE_PER_RELATIONSHIP;//???
    fp.back().costs_count = 1;//??
    fp.back().expected_pspace = r2_uid;//???

    //alignment constr
    vertical_alignment_constr_ID = fp.size(); //set id number to add more constraints to the solver
    fp.push_back(PSE_RELSHP_COST_FUNC_PARAMS_NULL);
    fids.push_back(PSE_RELSHP_COST_FUNC_ID_INVALID_);
    fp.back().compute = Constraints::vertical_alignment_constraint;
    fp.back().cost_arity_mode = PSE_COST_ARITY_MODE_PER_RELATIONSHIP;//???
    fp.back().costs_count = 1;
    fp.back().expected_pspace = r2_uid;

    //horizontal alignment constr
    horizontal_alignment_constr_ID = fp.size();
    fp.push_back(PSE_RELSHP_COST_FUNC_PARAMS_NULL);
    fids.push_back(PSE_RELSHP_COST_FUNC_ID_INVALID_);
    fp.back().compute = Constraints::horizontal_alignment_constraint;
    fp.back().cost_arity_mode = PSE_COST_ARITY_MODE_PER_RELATIONSHIP;//???
    fp.back().costs_count = 1;
    fp.back().expected_pspace = r2_uid;


}

void MyDecalSolver::internal_preupdate_constraintrelationships(size_t nRelshsps, std::vector< std::array<pse_ppoint_id_t, 2> > pppairs)
{

    //gamut constr
    pse_cpspace_relshp_params_t grp = PSE_CPSPACE_RELSHP_PARAMS_NULL_;
    pse_relshp_id_t grid = PSE_RELSHP_ID_INVALID;
    grp.ppoints_count = 0;
    grp.ppoints_id = nullptr;
    grp.kind = PSE_RELSHP_KIND_EXCLUSIVE;
    grp.cnstrs.funcs_count = 1;
    grp.cnstrs.funcs = &fids[gamut_cosntr_ID];
    grp.cnstrs.ctxts_config = gamut_config; // gives access to the current state
    PSE_CALL(pseConstrainedParameterSpaceRelationshipsAdd(cps,gamut_cosntr_ID,1,&grp,&grid));

    //vertical line alignment constr
    pse_cpspace_relshp_params_t grp2 = PSE_CPSPACE_RELSHP_PARAMS_NULL_;
    pse_relshp_id_t grid2 = PSE_RELSHP_ID_INVALID;
    grp2.ppoints_count = 0;
    grp2.ppoints_id = nullptr;
    grp2.kind = PSE_RELSHP_KIND_EXCLUSIVE;
    grp2.cnstrs.funcs_count = 1;
    grp2.cnstrs.funcs = &fids[vertical_line_alignment_constr_ID];
    grp2.cnstrs.ctxts_config = gamut_config; // gives access to the current state
    PSE_CALL(pseConstrainedParameterSpaceRelationshipsAdd(cps, vertical_line_alignment_constr_ID,1,&grp2,&grid2));

    //horizontal alignment constr
    pse_cpspace_relshp_params_t grp3 = PSE_CPSPACE_RELSHP_PARAMS_NULL_;
    pse_relshp_id_t grid3 = PSE_RELSHP_ID_INVALID;
    grp3.ppoints_count = 0;
    grp3.ppoints_id = nullptr;
    grp3.kind = PSE_RELSHP_KIND_EXCLUSIVE;
    grp3.cnstrs.funcs_count = 1;
    grp3.cnstrs.funcs = &fids[horizontal_line_alignment_constr_ID];
    grp3.cnstrs.ctxts_config = gamut_config; // gives access to the current state
    PSE_CALL(pseConstrainedParameterSpaceRelationshipsAdd(cps, horizontal_line_alignment_constr_ID,1,&grp3,&grid3));

    //fixed position constr
    pse_cpspace_relshp_params_t grp4 = PSE_CPSPACE_RELSHP_PARAMS_NULL_;
    pse_relshp_id_t grid4 = PSE_RELSHP_ID_INVALID;
    grp4.ppoints_count = 0;
    grp4.ppoints_id = nullptr;
    grp4.kind = PSE_RELSHP_KIND_EXCLUSIVE;
    grp4.cnstrs.funcs_count = 1;
    grp4.cnstrs.funcs = &fids[fixed_position_constr_ID];
    grp4.cnstrs.ctxts_config = gamut_config; // gives access to the current state
    PSE_CALL(pseConstrainedParameterSpaceRelationshipsAdd(cps, fixed_position_constr_ID,1,&grp4,&grid4));

    //min dist constr
    std::vector<pse_cpspace_relshp_params_t> rp(nRelshsps, PSE_CPSPACE_RELSHP_PARAMS_NULL_);
    std::vector<pse_relshp_id_t> rids(nRelshsps, PSE_RELSHP_ID_INVALID_) ;
    for(size_t i = 0; i < nRelshsps; i++) {
      rp[i].ppoints_count = 2;
      rp[i].ppoints_id = pppairs[i].data();
      rp[i].kind = PSE_RELSHP_KIND_INCLUSIVE;
      rp[i].cnstrs.funcs_count = 1;
      rp[i].cnstrs.ctxts_config = gamut_config;// name is the same, but it is the state
      rp[i].cnstrs.funcs = &fids[min_dist_cosntr_ID];
    }
    PSE_CALL(pseConstrainedParameterSpaceRelationshipsAdd(cps, min_dist_cosntr_ID,nRelshsps,rp.data(),rids.data()));

    //max dist constr
    std::vector<pse_cpspace_relshp_params_t> rp1(nRelshsps, PSE_CPSPACE_RELSHP_PARAMS_NULL_) ;
    std::vector<pse_relshp_id_t> r1ids(nRelshsps, PSE_RELSHP_ID_INVALID_) ;
    for(size_t i = 0; i < nRelshsps; i++) {
      rp1[i].ppoints_count = 2;
      rp1[i].ppoints_id = pppairs[i].data();
      rp1[i].kind = PSE_RELSHP_KIND_INCLUSIVE;
      rp1[i].cnstrs.funcs_count = 1;
      rp1[i].cnstrs.ctxts_config = gamut_config;// name is the same, but it is the state
      rp1[i].cnstrs.funcs = &fids[max_dist_cosntr_ID];
    }
    PSE_CALL(pseConstrainedParameterSpaceRelationshipsAdd(cps,max_dist_cosntr_ID,nRelshsps,rp1.data(),r1ids.data()));

    //vertical gamut alignment constr
    std::vector<pse_cpspace_relshp_params_t> rp2(nRelshsps, PSE_CPSPACE_RELSHP_PARAMS_NULL_);
    std::vector<pse_relshp_id_t> r2ids(nRelshsps, PSE_RELSHP_ID_INVALID_) ;
    for(size_t i = 0; i < nRelshsps; i++) {
      rp2[i].ppoints_count = 2;
      rp2[i].ppoints_id = pppairs[i].data();
      rp2[i].kind = PSE_RELSHP_KIND_INCLUSIVE;
      rp2[i].cnstrs.funcs_count = 1;
      rp2[i].cnstrs.ctxts_config = gamut_config;// name is the same, but it is the state
      rp2[i].cnstrs.funcs = &fids[vertical_alignment_constr_ID];
    }
    PSE_CALL(pseConstrainedParameterSpaceRelationshipsAdd(cps, vertical_alignment_constr_ID,nRelshsps,rp2.data(),r2ids.data()));

    //horizontal gamut alignment constr
    std::vector<pse_cpspace_relshp_params_t> rp3(nRelshsps, PSE_CPSPACE_RELSHP_PARAMS_NULL_);
    std::vector<pse_relshp_id_t> r3ids(nRelshsps, PSE_RELSHP_ID_INVALID_) ;
    for(size_t i = 0; i < nRelshsps; i++) {
      rp3[i].ppoints_count = 2;
      rp3[i].ppoints_id = pppairs[i].data();
      rp3[i].kind = PSE_RELSHP_KIND_INCLUSIVE;
      rp3[i].cnstrs.funcs_count = 1;
      rp3[i].cnstrs.ctxts_config = gamut_config;// name is the same, but it is the state
      rp3[i].cnstrs.funcs = &fids[horizontal_alignment_constr_ID];
    }
    PSE_CALL(pseConstrainedParameterSpaceRelationshipsAdd(cps, horizontal_alignment_constr_ID,nRelshsps,rp3.data(),r3ids.data()));

}


void MyDecalSolver::internal_preupdate_assignnpoints(){
    nPoints = decales.size();
}

void MyDecalSolver::internal_preupdate_mapping(std::vector<pse_ppoint_id_t> ppids){
    mydecalsmap.clear();
    for(size_t i = 0; i< nPoints; i++){
        mydecalsmap.insert({ppids[i],decales[i]});
    }
}

void MyDecalSolver::internal_preupdate_setHandlers(){
    coords_data.as.global.accessors.get = getAttribs;
    coords_data.as.global.accessors.set = setAttribs;
}

pse_res_t MyDecalSolver::getAttribs(void *ctxt,
                                    const pse_point_attrib_t attrib,
                                    const pse_type_t as_type,
                                    const size_t count,
                                    const pse_ppoint_id_t *values_idx,
                                    void *attrib_values){
    size_t i;
    (void)as_type;
    (void)ctxt;

    switch(attrib) {
    case PSE_POINT_ATTRIB_COORDINATES: {
        pse_real_t* out = static_cast<pse_real_t*>(attrib_values);
        assert(as_type == PSE_TYPE_REAL);
        for(i = 0; i < count; ++i) {
            const pse_ppoint_id_t ppid = values_idx[i];

            out[i*2+0] = pse_real_t(mydecalsmap[ppid]->getPosx());
            out[i*2+1] = pse_real_t(mydecalsmap[ppid]->getPosy());
        }
    } break;
    case PSE_POINT_ATTRIB_LOCK_STATUS: {
          //locking only the movable point
        uint8_t* out = static_cast<uint8_t*>(attrib_values);
        assert(as_type == PSE_TYPE_BOOL_8);
        for(i = 0; i < count; ++i) {
            const pse_ppoint_id_t ppid = values_idx[i];
            (void)ppid;
            //reverse mapping
            std::map<pse_ppoint_id_t, DecaleScalarField2D*>::iterator it;
            it = mydecalsmap.find(ppid);

            if(QWidgetMyDecale::lockedDecals.at(it->first)== true){//active when pressed by user
                out[i] = 1 ;
            }else out[i] = 0;
        }
      } break;
    default: assert(false);
    }
    return RES_OK;
}

pse_res_t MyDecalSolver::setAttribs(void *ctxt,
                                    const pse_point_attrib_t attrib,
                                    const pse_type_t as_type,
                                    const size_t count,
                                    const pse_ppoint_id_t *values_idx,
                                    const void *attrib_values){
    size_t i;
    (void)as_type;
    (void)ctxt;

    switch(attrib) {
        case PSE_POINT_ATTRIB_COORDINATES: {
            const pse_real_t* in = static_cast<const pse_real_t*>(attrib_values);
            assert(as_type == PSE_TYPE_REAL);
            for(i = 0; i < count; ++i) {

                const pse_ppoint_id_t ppid = values_idx[i];

                mydecalsmap[ppid]->setPosx(in[i*2+0]);//qreal
                mydecalsmap[ppid]->setPosy(in[i*2+1]);
            }
        } break;
        default: assert(false);
    }
    return RES_OK;
}




