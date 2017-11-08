%% Problem on adding noise to mesh
%
% Authors : Trung-Thien Tran
% Emal:       trung-thien.tran.1@ulaval.ca; 
%             tranthien9.vn@gmail.com
% Created : 21/05/2014
% Upadted : 
% This implementation copyright Trung-Thien Tran 2014, vision.gel.ulaval.ca, but 
% is freely available to copy, use, or modify as long as this line is maintained
function vertex1=add_noise_mesh(vertex,faces,sigma)

n = size(vertex,1);
% compute the normals
normals = compute_normal(vertex,faces);
dist=0;

for i=1:100
  p=randsample(n,1); 
  neigh_vertex=find_vertex_1neighbor(faces,p);
  tmp=size(neigh_vertex,2);
  tmp=repmat(vertex(p,:),tmp,1)-vertex(neigh_vertex,:);
  tmp=sum(sqrt(sum(tmp.*tmp,2)))/size(neigh_vertex,2);
  dist=dist+tmp/100;
end

% add some noise to the vertices
sigma = sigma/100*dist; % noise level
rho = (randn(1,n)-0.5)*sigma;
vertex1 = vertex + (repmat(rho,3,1).*normals)';