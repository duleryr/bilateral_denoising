%% This function aim at finding 2-ring neighborhood vertex of certain vertex
% Input: faces dada and vertex in processing   n*3-faces
% Output: list of neighbor vertex   n*1-vertex
% 
% Trung-Thien Tran; ulaval.ca; tranthien9.vn@gmail.com
% 6/12/2012
%%
function  neigh_vertex=find_vertex_2neighbor(faces,i)


neigh_vertex1=find_vertex_1neighbor(faces,i);
k=size(neigh_vertex1,2);
neigh_vertex2=zeros(k,[]);
 for j=1:k
  output=find_vertex_1neighbor(faces,neigh_vertex1(j));
  neigh_vertex2(j,1:size(output,2))= output;
 end
 
Order=unique(neigh_vertex2);  % make it in order
neigh_vertex =Order(Order~=0,1)' ; % output vertex
neigh_vertex =neigh_vertex(neigh_vertex~=i);  % output vertex
